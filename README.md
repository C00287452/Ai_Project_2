<div align="center">

# ❄️ Coding Valley ❄️

### *Learn C and C++ in a cosy snowy campus, one little win at a time.*

🌲 🏡 ⛄ 🌲 🕯️ 🌲 ⛄ 🏡 🌲

**Walk the campus · Meet your teachers · Write real code · Watch it run**

</div>

---

## 🎄 Welcome to the Valley

Coding Valley is a warm little game about learning to program. You arrive on a snowy campus with a lantern-lit path, step into the **C Hall** or **C++ Hall**, learn something new, and then go and *try it for real* in a built-in coding lab that compiles and runs your own programs.

No dry textbook. No blank page. Just a cosy world with a lot of ways to practise, and a streak that glows a bit brighter every day you come back. 🔥

It is written in C with [raylib](https://www.raylib.com/), lives in a single source file, and compiles as both C99 and C++.

---

## ✨ What's waiting for you

### 📖 Learn
Five lessons per language with colourful syntax-highlighted code, a quiz after each one (pick an answer or type it), friendly explanations, mastery levels and a notes page of your own. Tap **"Try this code in the Lab"** to run any example straight away.

### 🧩 Practice
**58 auto-graded problems** from Easy to Hard. Write a solution, or **fix a broken program**. Every submission is compiled and run against test cases, with three gentle hints and a worked solution when you want one.

### 💻 Coding Lab
Your own free editor with line numbers and highlighting. Press **Run (F5)** and your C or C++ is built by a real compiler, with output, errors, warnings and keyboard input. Nine starter examples to play with.

### 🔍 Code Breakdown
Watch **20 programs** run line by line, with the stack and heap drawn as crates and hay bales. Try *predict mode*: guess the next step before it happens.

### 🪜 Code Stepper
The same step-by-step view, but for *your own* code.

### 🐛 Bug Hunt
Ride a **mine cart** through a glowing crystal cave and find the one wrong line in each program. **37 bugs** in 6 topic tunnels: Loops, Conditions, Numbers, Arrays and strings, Memory and pointers, and Functions. Every bug comes with a clear explanation.

### 🧰 Valley Jobs
**15 longer coding jobs** with several tests each, for when you want a real challenge.

### 🚜 Mower Farm
A programming game inside the game. Write C or C++ to drive your ride-on mower, grow crops and buy upgrades. It has its own tiny compiler, 10 examples per language and a tutorial.

### 🌟 Study Hub
Spaced review of the questions you missed, timed speed rounds, a skills page, saved notes, search, a **skill map** and a glossary.

### 🏫 Campus, Arena and Shop
Explore the campus, chat with **ten teachers** across the two halls, duel rivals in the Battle Arena, grab the daily quest from the little gold hut, and spend your credits on cosmetics in the shop.

### 🏆 Progress that feels good
XP, levels, a day streak, mastery names and credits. Switch the **C / C++** toggle at any time and everything follows.

---

## 🎁 Quick start

### What you need
- 🖥️ [raylib](https://www.raylib.com/) 4.x or 5.x and a C compiler (gcc / MinGW-w64 on Windows).
- 🛠️ **`gcc` and `g++` on your PATH**, because the Lab, Practice, Jobs and Farm use them to build your code. If they are missing, the app tells you kindly instead of crashing.
- 🔤 Fonts are built in, so there are no extra files to find.

### Build it

**Windows** (w64devkit with raylib, same as `build_c.bat`)

```bat
set PATH=C:\raylib\w64devkit\bin;%PATH%
gcc -o codequest.exe main.c -O2 -std=c99 -static -lraylib -lopengl32 -lgdi32 -lwinmm -lshcore
```

> 💡 Prefer a double-click? `build_c.bat` builds `codequest.c` (an identical copy of `main.c`) and starts the game.

**Linux**

```sh
gcc main.c -o codequest -O2 -std=c99 -lraylib -lGL -lm -lpthread -ldl -lrt -lX11
```

**macOS**

```sh
gcc main.c -o codequest -O2 -std=c99 -lraylib -framework OpenGL -framework Cocoa -framework IOKit
```

**Make sure it still builds as both languages**

```sh
gcc -std=c99 -Wall -fsyntax-only -I<raylib include dir> main.c
g++ -x c++ -fsyntax-only -I<raylib include dir> main.c
```

---

## 🎮 Controls

| Where | Keys |
| --- | --- |
| 🏫 Campus | Arrows or WASD to walk, **Shift** to run, **Space** to talk or go in, **Esc** for the study menu |
| 🖱️ Menus | Click, scroll with the wheel, **Esc** to go back |
| 📖 Lessons | **← →** to change page |
| 💻 Coding Lab | **F5** or **Ctrl+Enter** to run, Ctrl+A / C / X / V, **Tab** for 4 spaces, **Esc** to leave (your code is kept) |
| 🪟 Anywhere | **F11** or **Alt+Enter** for fullscreen; resize the window as you like |

---

## 💾 Your progress

The game saves in the folder it runs from, so launch it from the same place each time:

`progress.dat` · `profile.dat` · `quest.dat` · `game.dat` · `problems.dat` · `jobs.dat` · `jobs_code.dat` · `study.dat` · `notes.dat` · `settings.dat` · `farm2.dat` · `farm_c.txt` · `farm_cpp.txt`

Want a fresh start? Delete a file to reset that part. (An old `farm2_code.txt` from the earlier farm is ignored.)

---

## 🧊 Good to know

- The Coding Lab builds your program with your own compiler and stops it after **3 seconds**. It is **not a sandbox**, so run only code you wrote, on your own computer.
- The window pauses for a moment while your code compiles.
- The Code Stepper can't yet follow structs, classes, enums, `malloc` / `new`, 2-D arrays or `vector<string>`.
- The Mower Farm uses a friendly subset of C and C++: no pointers, structs, `switch`, `malloc` / `new`, 2-D arrays or input. Programs start with `int main(void)` (C) or `int main()` (C++).
- Saves are simple raw files with no backups yet.
- Still to come: sound, a first-run tutorial and accessibility options.
- There are no automated tests in the repo yet.

---



## 📁 What's in the box

```
main.c        the whole game (also kept as codequest.c)
build_c.bat   Windows build-and-run script
README.md     you are here ⛄
```

---

## 🙏 Credits

Made with C and [raylib](https://www.raylib.com/). Fonts: Liberation Serif (SIL Open Font License) and DejaVu Sans Mono (free licence).

<div align="center">

🌲 ⛄ 🏡 🕯️ 🏡 ⛄ 🌲

**Grab a hot chocolate, open the Lab, and write your first line of code.** ☕

</div>
