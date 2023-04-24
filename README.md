# Terminal Maze with Configurable Visibility

- **Unit**: Unix and C Programming (`COMP1000` / `UCP1000`) — Assignment 1
- **Study Period**: 2023 Trimester 1A
- **Degree Programme**: Bachelor of Information Technology — Awarded with Distinction by Curtin University
- **Overall Unit Mark**: 90 (High Distinction)

> **README for Assignment Submission**: [README for Assignment Submission](ORIGINAL_README.md)

## Assignment context

The first Unix and C Programming assignment required a C89 maze game for a Linux terminal. The player explores a two-dimensional map, collects a key and brings it to the exit. The task emphasized dynamic memory allocation, modular `.c`/`.h` files, a handwritten Makefile, immediate single-character input and correct memory cleanup.

The visibility feature was part of the task: conditional compilation with `DARK` enables a non-negative distance around the player's position. A distance of zero shows the entire map; a positive distance shows a square region extending that many rows and columns in each direction.

The task supplied world-data and terminal-input helpers. The author integrated those helpers with map construction, rendering, movement, key/exit state and the game loop. This project precedes [Assignment 2 with a pursuer and undo history](../Terminal-Maze-Survival-Game/).

## Implementation

| Files | Responsibility |
|---|---|
| `main.c` | Argument handling, map allocation, initialization, game loop and cleanup |
| `game.c` / `game.h` | Movement, collisions, key acquisition and winning state |
| `map.c` / `map.h` | Map rendering and square visibility clipping |
| `world.c` / `world.h` | Supplied world description and object positions |
| `terminal.c` / `terminal.h` | Terminal settings for input without pressing Enter |
| `algorithm.c` / `algorithm.h` | Minimum and maximum helpers used for bounds |

## Build and play

Use a Linux or WSL terminal with GCC and Make. Run these commands in this directory:

```bash
make
./maze 3
```

The Makefile uses `-Wall -pedantic -ansi` and defines `DARK` when compiling the entry point. The implementation also accepts no distance argument and defaults to full visibility:

```bash
./maze
./maze 0
./maze 1
```

Press any key at the welcome screen. Use lowercase `w`, `a`, `s`, `d` to move and `q` to quit. Collect `k` before reaching `x`. Enter is not required for each move.

```bash
make clean
```
