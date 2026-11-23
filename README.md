# Coding Valley 

**Learn C and C++ by exploring a snowy campus, writing real code and watching it run.**

Coding Valley is a desktop learning game written in C with [raylib](https://www.raylib.com/). You walk around a campus, take lessons from teachers in the C Hall and C++ Hall, and practise in a built-in coding lab that compiles and runs your own programs. It is one source file (about 16,400 lines) and it compiles as both C99 and C++.

## What you can do

| Space | What it is |
| --- | --- |
| **Learn** | 5 lessons per language with syntax-highlighted code, a quiz after each lesson (multiple choice or type the answer), explanations, mastery levels and your own notes. A "Try this code in the Lab" button opens the example in the editor. |
| **Practice** | 58 auto-graded problems (Easy, Medium, Hard). Two kinds: write a solution, or fix a broken program. Every submission is compiled and run against test cases. Three progressive hints and a worked solution with an explanation. |
| **Coding Lab** | A free editor with line numbers and syntax highlighting. Press Run (F5 or Ctrl+Enter) to compile and run your C or C++ with a real compiler. Shows output, compiler errors and warnings, takes keyboard input, and has 9 starter examples. |
| **Code Breakdown** | 20 programs you step through line by line, with the stack and heap drawn as crates and hay bales, plus a predict-the-next-step mode. |
| **Code Stepper** | The same step-by-step view for your own code, from the Lab or from a Practice problem. |
| **Bug Hunt** | Find the one wrong line in a short program. 37 bugs (19 in C, 18 in C++) in 6 topic tunnels (Loops, Conditions, Numbers, Arrays and strings, Memory and pointers, Functions), reached by mine cart. Each bug comes with an explanation. |
| **Valley Jobs** | 15 longer coding jobs with several tests each. |
| **Mower Farm** | A programming game: write C or C++ to drive a ride-on mower, grow crops and buy upgrades. Has its own C/C++ compiler and virtual machine, 10 examples per language, and a tutorial. |
| **Study hub** | Spaced review of questions you missed, timed speed rounds, a skills page, saved questions and notes, search, a skill map and a glossary. |
| **Campus and Arena** | A walkable campus with the C Hall, C++ Hall (5 teachers each), a shop, a daily quest hut and a Battle Arena where you duel rivals with timed questions. |
| **Progress** | XP, levels, a day streak, mastery names, credits and a shop for cosmetics. |

Everything with code follows the **C / C++ toggle** in the sidebar.

## Requirements

- **raylib 4.x or 5.x** and a C compiler (gcc / MinGW-w64 on Windows).
- **To use the Coding Lab, Practice, Jobs and Farm checks you also need `gcc` and `g++` on your PATH.** The app compiles your code with them. If they are missing, it tells you so instead of crashing.
- Fonts (Liberation Serif and DejaVu Sans Mono) are embedded in the source, so no asset files are needed.

## Build

Put the source file where you build it and run one of these.

**Windows (w64devkit with raylib, as in `build_c.bat`)**

```bat
set PATH=C:\raylib\w64devkit\bin;%PATH%
gcc -o codequest.exe main.c -O2 -std=c99 -static -lraylib -lopengl32 -lgdi32 -lwinmm -lshcore
```

`build_c.bat` does exactly this for `codequest.c`; `main.c` is an identical copy.

**Linux**

```sh
gcc main.c -o codequest -O2 -std=c99 -lraylib -lGL -lm -lpthread -ldl -lrt -lX11
```

**macOS**

```sh
gcc main.c -o codequest -O2 -std=c99 -lraylib -framework OpenGL -framework Cocoa -framework IOKit
```

To check that it still compiles as both languages:

```sh
gcc -std=c99 -Wall -fsyntax-only -I<raylib include dir> main.c
g++ -x c++ -fsyntax-only -I<raylib include dir> main.c
```

## Controls

| Where | Keys |
| --- | --- |
| Campus | Arrows or WASD to move, Shift to run, Space to talk or enter, Esc for the study menu |
| Menus | Mouse to click, mouse wheel to scroll, Esc to go back |
| Lessons | Left and Right arrows change page |
| Coding Lab | F5 or Ctrl+Enter run, Ctrl+A / C / X / V, Tab inserts 4 spaces, Esc leaves (your code is kept) |
| Anywhere | F11 or Alt+Enter toggles fullscreen; the window can be resized (minimum 600x380) |

## Saved data

The game saves next to where it is run, in the current folder:

`progress.dat`, `profile.dat`, `quest.dat`, `game.dat`, `problems.dat`, `jobs.dat`, `jobs_code.dat`, `study.dat`, `notes.dat`, `settings.dat`, `farm2.dat`, `farm_c.txt`, `farm_cpp.txt`

Delete a file to reset that part of your progress. Run the game from the same folder each time. The farm saves C and C++ programs separately; an old `farm2_code.txt` from the earlier Python-style farm is ignored.

## Known limits

- The Coding Lab runs your program with the machine's own compiler and a 3-second time limit. **It is not a sandbox**, so only run code you wrote, on your own computer.
- Compiling and running happens on the main thread, so the window pauses briefly while code builds.
- The Code Stepper does not yet handle structs, classes, enums, `malloc`/`new`, 2-D arrays or `vector<string>`.
- The Mower Farm language is a subset of C/C++: no pointers, structs, `switch`, `malloc`/`new`, 2-D arrays or input. Programs need `int main(void)` (C) or `int main()` (C++).
- Save files are raw structs written directly; there is no versioned backup for `progress.dat`.
- There is no audio, no first-run tutorial for the main game, and no accessibility options beyond fullscreen yet.
- There are no automated tests in the repository.

## Project layout

```
main.c        the whole game (also kept as codequest.c)
build_c.bat   Windows build and run script
README.md     this file
```

## Roadmap

A written audit lists the priorities: safe saves, a first-run tutorial and Continue card, tasks on every lesson page, linking failed tests to the matching lesson, practice problems for pointers, structs and recursion, coding duels in the Arena, achievements, and accessibility options (text size, reduce motion, colour-blind palette, keyboard navigation).

## Credits

Written in C with [raylib](https://www.raylib.com/). Fonts: Liberation Serif (SIL Open Font License) and DejaVu Sans Mono (free licence).
