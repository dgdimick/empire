# VMS Empire

VMS Empire is a classic turn-based strategy game played in a text terminal. Units, cities, land, and water are represented using letters and ASCII characters.

This fork includes compatibility fixes for modern Linux systems, including Raspberry Pi OS, along with an AI-versus-AI spectator mode.

## Changes in This Fork

* Added AI-versus-AI spectator mode.
* Added selectable Blue, Red, Shared, and Full spectator views.
* Added live view switching during AI matches.
* Added blue and red terminal colors for the two AI empires.
* Added an end-of-game prompt to keep or delete `empsave.dat` and `info_list.txt`.
* Added the GCC `-fcommon` compiler option to fix multiple-definition linker errors on modern GCC versions.
* Corrected two map-array loops in `game.c`.

The affected loops were changed from:

```c
i <= MAP_SIZE
```

to:

```c
i < MAP_SIZE
```

This prevents the loops from accessing one element beyond the end of the map arrays.

## Requirements

Install the compiler, development tools, Git, and ncurses library:

```bash
sudo apt update
sudo apt install -y git build-essential libncurses-dev
```

## Download

Clone this fork:

```bash
git clone https://github.com/dgdimick/empire.git
cd empire
```

## Build

Compile the game:

```bash
make
```

The executable will be created as:

```text
vms-empire
```

## Normal Game Mode

Start the normal human-versus-computer game with:

```bash
./vms-empire
```

The AI additions do not replace or disable normal gameplay.

## AI-versus-AI Spectator Mode

Start an unattended match where the computer controls both empires:

```bash
./vms-empire -a
```

The `-a` option enables AI-versus-AI mode.

Use the `-d` option to set the delay between map updates in milliseconds.

Example with a 500-millisecond delay:

```bash
./vms-empire -a -d 500
```

Examples:

```bash
./vms-empire -a -d 1000
./vms-empire -a -d 500
./vms-empire -a -d 100
```

* `1000` = one second between updates
* `500` = half a second between updates
* `100` = fast playback

The Blue AI is displayed in blue and the Red AI is displayed in red on terminals that support color.

Press `Ctrl-C` to stop an active match.

## AI Spectator Views

The AI spectator mode supports four starting views.

### Blue fog-of-war view

Shows only territory and units known to the Blue AI:

```bash
./vms-empire -a -v blue
```

### Red fog-of-war view

Shows only territory and units known to the Red AI:

```bash
./vms-empire -a -v red
```

### Shared fog-of-war view

Shows anything discovered by either AI:

```bash
./vms-empire -a -v shared
```

### Full spectator view

Shows the entire battlefield:

```bash
./vms-empire -a -v full
```

The view option can be combined with the delay option:

```bash
./vms-empire -a -v shared -d 500
```

If `-v` is omitted, the game starts in Shared view:

```bash
./vms-empire -a -d 500
```

## Change Views During a Match

While an AI-versus-AI match is running, press:

```text
B = Blue fog-of-war view
R = Red fog-of-war view
S = Shared fog-of-war view
F = Full spectator view
```

These commands only change what the spectator sees. They do not alter either AI’s private map or give either side additional information.

## End-of-Game Save Prompt

At the end of an AI-versus-AI match, the game asks:

```text
Keep empsave.dat and info_list.txt? (Y/N)
```

Choose:

```text
Y = Keep both files
N = Delete both files
```

The files are:

* `empsave.dat` — the saved game state
* `info_list.txt` — the recorded move and game information

The final game position is saved before the prompt appears.

## Clean and Rebuild

To remove compiled files and rebuild from scratch:

```bash
make clean
make
```

A normal repository checkout should not contain compiled `.o` files or the `vms-empire` executable.

## Suggested PuTTY Window Size

The game map is 100 columns by 60 rows.

For a full-size spectator display in PuTTY, use approximately:

```text
Columns: 110
Rows: 65
```

Smaller terminals will use the condensed map display.

## Repository Remotes

This fork is maintained at:

```text
https://github.com/dgdimick/empire
```

The original repository is:

```text
https://github.com/slacy/empire
```

## Platform Tested

The changes in this fork were tested on Raspberry Pi OS using a Raspberry Pi.

## License

This fork retains the original project’s licensing and copyright terms. See the repository files for the original license information.
