# Ai_Project_2

# 🎓 CodeQuest – Interactive C & C++ Learning App

**CodeQuest** is an interactive programming education application designed to make learning C and C++ more engaging and enjoyable. Built using the C programming language and the [raylib](https://www.raylib.com/) graphics library, CodeQuest combines structured lessons, interactive quizzes and a virtual campus environment to create an immersive learning experience.

Instead of simply reading programming tutorials, users can explore a virtual campus, attend lessons, test their knowledge and challenge coding rivals in a Battle Arena.

---

## ✨ Features

### 📚 Interactive Programming Lessons
- Dedicated learning sections for C and C++.
- Structured lessons covering fundamental and advanced programming concepts.
- Syntax-highlighted code examples.
- Explanations accompanying programming examples.
- Multiple pages within each lesson.

### 📝 Interactive Quizzes
- Test your understanding with programming quizzes.
- Switch between multiple-choice questions and typed answers.
- Receive explanations after answering questions.
- View quiz results and scores.
- Retry quizzes or revisit lessons to improve your understanding.

### 🏫 Virtual Campus
- Explore an interactive campus environment.
- Visit the dedicated C Hall and C++ Hall.
- Interact with virtual teachers.
- Enter classrooms to access lessons and quizzes.
- Experience a more engaging approach to programming education.

### ⚔️ Coding Battle Arena
- Challenge virtual coding rivals.
- Compete in head-to-head programming duels.
- Face three different opponents with varying difficulty levels.
- Test your programming knowledge in a competitive environment.

### 📊 Progress Tracking
- Automatically save learning progress.
- Track completed lessons.
- Store best quiz scores.
- Keep track of defeated Battle Arena opponents.
- Progress is saved locally in `progress.dat`.

### 🎨 User Interface
- Graphical interface powered by raylib.
- Embedded fonts, meaning no external font files are required.
- Mouse and keyboard navigation.
- Scrollable lesson content.
- Syntax-highlighted programming examples.

---

## 🛠️ Technologies Used

| Technology | Purpose |
|---|---|
| C | Main programming language |
| raylib | Graphics and user interface |
| OpenGL | Graphics rendering |
| GCC | Compilation |
| Embedded Fonts | Application typography |

**Fonts included:**
- Liberation Serif
- DejaVu Sans Mono

Both fonts are embedded directly into the source code.

---

## 🚀 Installation and Setup

### Prerequisites

Before running CodeQuest, make sure you have:

- GCC compiler
- raylib graphics library
- A supported operating system (Windows, macOS or Linux)

### 1. Clone the repository

```bash
git clone https://github.com/YOUR-USERNAME/CodeQuest.git
```

Navigate into the project directory:

```bash
cd CodeQuest
```

### 2. Compile the application

**Linux**

```bash
gcc main.c -o codequest -lraylib -lGL -lm -lpthread -ldl -lrt -lX11
```

**macOS**

```bash
gcc main.c -o codequest -lraylib -framework OpenGL -framework Cocoa -framework IOKit
```

**Windows**

```bash
gcc main.c -o codequest.exe -lraylib -lopengl32 -lgdi32 -lwinmm
```

Make sure raylib is correctly installed and configured for your compiler.

### 3. Run CodeQuest

**Linux / macOS**

```bash
./codequest
```

**Windows**

```bash
codequest.exe
```

---

## 🎮 Controls and Navigation

| Control | Action |
|---|---|
| Mouse click | Select buttons and interact with the interface |
| Mouse wheel | Scroll through lesson content |
| Left Arrow | Previous lesson page |
| Right Arrow | Next lesson page |
| Space | Interact with teachers when nearby in campus mode |
| ESC | Go back or exit from the main menu |

In campus mode, explore the environment and enter the C Hall or C++ Hall through their doors. Approach a teacher and press Space to interact.

In the Battle Arena, challenge one of the available rivals to a coding duel.

---

## 💾 Progress Storage

CodeQuest automatically saves progress locally using a file called:

```text
progress.dat
```

This file stores:
- Lesson completion information.
- Best quiz scores.
- Battle Arena victories.

The progress file is created automatically when progress is saved.

---

## 📁 Project Structure

```text
CodeQuest/
│
├── main.c          # Main application source code
├── progress.dat    # Automatically generated progress data
└── README.md       # Project documentation
```

---

## 🎯 Project Goals

The main goal of CodeQuest is to make programming education more interactive and accessible.

By combining traditional programming lessons with gamification, quizzes and an explorable virtual environment, the application aims to encourage users to practise programming concepts while making the learning process more enjoyable.

---

## 🔮 Future Improvements

Potential future enhancements include:

- Additional C and C++ lessons.
- More advanced programming challenges.
- Additional Battle Arena opponents.
- Expanded quiz question banks.
- More campus environments and interactive features.
- Further progress statistics and achievements.

---

## 👥 Contributors

Contributions, suggestions and feedback are welcome.

If you would like to contribute:

1. Fork the repository.
2. Create a new branch.
3. Make your changes.
4. Submit a Pull Request for review.

---

## 📄 License

No licence has currently been specified for this project.

---

**CodeQuest – Learn. Practise. Compete. Level Up!** 🎓💻
