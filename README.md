# VMS Empire

VMS Empire is a classic turn-based strategy game played in a text terminal. Units, cities, land, and water are represented using letters and ASCII characters.

This fork includes small compatibility fixes that allow the game to compile cleanly on modern Linux systems, including Raspberry Pi OS.

## Changes in this fork

* Added the GCC `-fcommon` compiler option to fix multiple-definition linker errors on modern GCC versions.
* Corrected two map-array loops in `game.c`.
* Changed:

In line 126
```c
i <= MAP_SIZE
```

to:

```c
i < MAP_SIZE
```

This prevents the loops from accessing one element beyond the end of the arrays.

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

## Run

Start the game with:

```bash
./vms-empire
```

## Clean and rebuild

To remove compiled files and rebuild from scratch:

```bash
make clean
make
```

## Repository remotes

This fork is maintained at:

```text
https://github.com/dgdimick/empire
```

The original repository is:

```text
https://github.com/slacy/empire
```

## Platform tested

The changes in this fork were tested on Raspberry Pi OS using a Raspberry Pi.

## License

This fork retains the original project’s licensing and copyright terms. See the repository files for the original license information.



AI vs AI spectator mode
-----------------------

This fork adds an unattended spectator mode where the existing computer
player controls both empires. Start it with:

    ./vms-empire -a

Use the existing -d option to set the delay in milliseconds between map
updates. For example:

    ./vms-empire -a -d 500

The full battlefield is shown using the condensed map display. The USER-side AI
is shown in blue and the COMP-side AI is shown in red on color terminals. Press Ctrl-C
to stop an active game. At the end of a game, press any key to exit.


AI spectator views
------------------
Start an AI-versus-AI match in one of four views:

  ./vms-empire -a -v blue
  ./vms-empire -a -v red
  ./vms-empire -a -v shared
  ./vms-empire -a -v full

If -v is omitted, shared fog-of-war is used. During a match, press B, R,
S, or F to switch immediately between Blue, Red, Shared, and Full views.
These display modes do not alter either AI's private fog-of-war map.
