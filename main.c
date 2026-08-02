/*
 *    Copyright (C) 1987, 1988 Chuck Simmons
 *
 * See the file COPYING, distributed with empire, for restriction
 * and warranty information.
 */

/*
main.c -- parse command line for empire

options:

    -w water: percentage of map that is water.  Must be in the range
              10..90.  Default is 70.

    -s smooth: amount of smoothing performed to generate map.  Must
               be a nonnegative integer.  Default is 5.

    -d delay:  number of milliseconds to delay between output.
               default is 2000 (2 seconds).

    -S saveinterval: sets turn interval between saves.
               default is 10
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "empire.h"
#include "extern.h"

#define OPTFLAGS "av:w:s:d:S:f:"

static void startup_menu(int *delay_ms) {
  char input[64];
  int choice;

  (void)printf("VMS Empire 5.00 - AI Spectator Fork 1.0\n\n");
  (void)printf("1. Normal game\n");
  (void)printf("2. AI vs AI - Shared view\n");
  (void)printf("3. AI vs AI - Blue view\n");
  (void)printf("4. AI vs AI - Red view\n");
  (void)printf("5. AI vs AI - Full view\n");
  (void)printf("6. Quit\n\n");
  (void)printf("Select mode [1]: ");
  (void)fflush(stdout);

  if (fgets(input, sizeof(input), stdin) == NULL || input[0] == '\n')
    choice = 1;
  else
    choice = atoi(input);

  switch (choice) {
    case 1:
      ai_vs_ai = false;
      return;
    case 2:
      ai_vs_ai = true;
      spectator_view = VIEW_SHARED;
      break;
    case 3:
      ai_vs_ai = true;
      spectator_view = VIEW_BLUE;
      break;
    case 4:
      ai_vs_ai = true;
      spectator_view = VIEW_RED;
      break;
    case 5:
      ai_vs_ai = true;
      spectator_view = VIEW_FULL;
      break;
    case 6:
      exit(0);
    default:
      (void)printf("Invalid selection. Starting normal game.\n");
      ai_vs_ai = false;
      return;
  }

  (void)printf("Delay between updates in milliseconds [500]: ");
  (void)fflush(stdout);
  if (fgets(input, sizeof(input), stdin) != NULL && input[0] != '\n') {
    int entered_delay = atoi(input);
    if (entered_delay >= 0 && entered_delay <= 30000)
      *delay_ms = entered_delay;
    else
      (void)printf("Invalid delay. Using 500 milliseconds.\n");
  }
}

int main(argc, argv) int argc;
char *argv[];
{
  int c;
  extern char *optarg;
  extern int optind;
  int errflg = 0;
  int wflg, sflg, dflg, Sflg;
  int land;

  wflg = 70; /* set defaults */
  sflg = 5;
  dflg = 2000;
  Sflg = 10;
  savefile = "empsave.dat";
  ai_vs_ai = false;
  spectator_view = VIEW_SHARED;

  if (argc == 1) {
    dflg = 500;
    startup_menu(&dflg);
  }

  /*
   * extract command line options
   */

  while ((c = getopt(argc, argv, OPTFLAGS)) != EOF) {
    switch (c) {
      case 'a':
        ai_vs_ai = true;
        break;
      case 'v':
        if (strcmp(optarg, "blue") == 0)
          spectator_view = VIEW_BLUE;
        else if (strcmp(optarg, "red") == 0)
          spectator_view = VIEW_RED;
        else if (strcmp(optarg, "shared") == 0)
          spectator_view = VIEW_SHARED;
        else if (strcmp(optarg, "full") == 0)
          spectator_view = VIEW_FULL;
        else {
          (void)printf("empire: -v must be blue, red, shared, or full.\n");
          exit(1);
        }
        break;
      case 'w':
        wflg = atoi(optarg);
        break;
      case 's':
        sflg = atoi(optarg);
        break;
      case 'd':
        dflg = atoi(optarg);
        break;
      case 'S':
        Sflg = atoi(optarg);
        break;
      case 'f':
        savefile = optarg;
        break;
      case '?': /* illegal option? */
        errflg++;
        break;
    }
  }
  if (errflg || (argc - optind) != 0) {
    (void)printf("empire: usage: empire [-a] [-v blue|red|shared|full] [-w water] [-s smooth] [-d delay]\n");
    exit(1);
  }

  if (wflg < 10 || wflg > 90) {
    (void)printf("empire: -w argument must be in the range 0..90.\n");
    exit(1);
  }
  if (sflg < 0) {
    (void)printf("empire: -s argument must be greater or equal to zero.\n");
    exit(1);
  }

  if (dflg < 0 || dflg > 30000) {
    (void)printf("empire: -d argument must be in the range 0..30000.\n");
    exit(1);
  }

  SMOOTH = sflg;
  WATER_RATIO = wflg;
  delay_time = dflg;
  save_interval = Sflg;

  /* compute min distance between cities */
  land = MAP_SIZE * (100 - WATER_RATIO) / 100; /* available land */
  land /= NUM_CITY;                            /* land per city */
  MIN_CITY_DIST = isqrt(land);                 /* distance between cities */

  empire(); /* call main routine */
  return (0);
}
