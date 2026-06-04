<div align="center">


<pre>
<img src="piscine-simulator/data/banner.png" height="100" />
</pre>

<br>

<img src="https://img.shields.io/badge/language-C-00599C?style=for-the-badge&logo=c&logoColor=white" alt="C">
<img src="https://img.shields.io/badge/build-Makefile-427819?style=for-the-badge&logo=gnu&logoColor=white" alt="Makefile">
<img src="https://img.shields.io/badge/interface-Terminal-111827?style=for-the-badge&logo=gnometerminal&logoColor=white" alt="Terminal">
<img src="https://img.shields.io/badge/style-42%20%2F%201337-000000?style=for-the-badge" alt="42 / 1337">

<br><br>

<img src="https://img.shields.io/badge/version-1.0.0-06b6d4?style=flat-square">
<img src="https://img.shields.io/badge/license-MIT-10b981?style=flat-square">
<img src="https://img.shields.io/badge/platform-Linux%20%7C%20macOS-8b5cf6?style=flat-square">
<img src="https://img.shields.io/badge/dependencies-none-f59e0b?style=flat-square">

<br><br>

<p align="center">
  <strong>🎓 A lightweight terminal exam simulator inspired by the 1337 / 42 piscine environment.</strong><br>
  <em>Practice your C skills in an authentic exam atmosphere. No internet, no IDE, just you and the terminal.</em>
</p>

<br>


[🚀 Quick Start](#-quick-start)
•
[📖 Documentation](#-overview)
•
[📊 Exam Rules](#-exam-rules)
•
[🔧 Commands](#-make-commands)
•
[📁 Structure](#-project-structure)

</div>

---

<br>

## 📋 Table of Contents

- [🎯 Overview](#-overview)
- [✨ Features](#-features)
- [⚡ Requirements](#-requirements)
- [🚀 Quick Start](#-quick-start)
- [🎮 How To Use](#-how-to-use)
- [✅ Validation Flow](#-validation-flow)
- [📊 Exam Rules](#-exam-rules)
- [🔧 Make Commands](#-make-commands)
- [🗂️ Project Structure](#-project-structure)
- [🐛 Troubleshooting](#-troubleshooting)
- [📝 Notes](#-notes)
- [🤝 Contributing](#-contributing)
- [📜 License](#-license)

<br>

---

<br>

## 🎯 Overview

<div align="center">

```
┌─────────────────────────────────────────────────────────────────────────────┐
│                                                                             │
│   ┌──────────┐    ┌──────────┐    ┌──────────┐    ┌──────────┐              │
│   │  Exam 00 │───▶│  Exam 01 │───▶│  Exam 02 │───▶│  Exam 03 │              │
│   └──────────┘    └──────────┘    └──────────┘    └──────────┘              │
│        │               │               │               │                    │
│        ▼               ▼               ▼               ▼                    │
│   ┌──────────┐    ┌──────────┐    ┌──────────┐    ┌──────────┐              │
│   │ Level 01 │    │ Level 01 │    │ Level 01 │    │ Level 01 │              │
│   │ Level 02 │    │ Level 02 │    │ Level 02 │    │ Level 02 │              │
│   │   ...    │    │   ...    │    │   ...    │    │   ...    │              │
│   │ Level 08 │    │ Level 08 │    │ Level 08 │    │ Level 16 │              │
│   └──────────┘    └──────────┘    └──────────┘    └──────────┘              │
│                                                                             │
│                         🏁 TARGET: 100 / 100                                │
│                                                                             │
└─────────────────────────────────────────────────────────────────────────────┘
```

</div>

**Piscine Simulator** recreates the iconic 42-style exam flow directly in your terminal. It is designed to help students practice under realistic exam conditions — randomized exercises, strict compilation flags, time pressure, and level-based progression.

### The Exam Loop

```
    ┌─────────────┐
    │  Start Exam │
    └──────┬──────┘
           │
           ▼
    ┌─────────────┐     ┌─────────────┐
    │ Get Random  │────▶│  Write Code │
    │  Exercise   │     │  in rendu/  │
    └──────┬──────┘     └──────┬──────┘
           │                    │
           │         ┌──────────┘
           │         ▼
           │    ┌─────────────┐
           │    │   test      │◀──────────┐
           │    │  (compile)  │           │
           │    └──────┬──────┘           │
           │           │                   │
           │     ┌─────┴─────┐             │
           │     │           │             │
           │     ▼           ▼             │
           │  ┌─────┐    ┌─────┐          │
           │  │ ❌  │    │ ✅  │          │
           │  │Fail │    │Pass │          │
           │  └──┬──┘    └──┬──┘          │
           │     │          │              │
           │     ▼          ▼              │
           │  ┌─────┐    ┌─────────┐      │
           │  │Stay │    │  submit │      │
           │  │Same  │    │         │      │
           │  │Level │    └────┬────┘      │
           │  └──┬──┘         │            │
           │     │            ▼            │
           │     │       ┌─────────┐       │
           └─────┴──────▶│  Next   │       │
                         │  Level  │───────┘
                         └─────────┘
```

<br>

---

<br>

## ✨ Features

### Core Features

| Feature | Description | Status |
|:--------|:------------|:------:|
| 🎓 **4 Exam Tracks** | `exam00` through `exam03` with progressive difficulty | ✅ |
| 📝 **240 Exercises** | Full subject pool covering all C fundamentals | ✅ |
| 🎲 **Random Picker** | Smart randomization with anti-repetition per session | ✅ |
| 📈 **Level Progression** | Automatic score tracking and level unlocking | ✅ |
| ⏱️ **Exam Timers** | Realistic 4h and 8h exam durations | ✅ |
| 🔄 **Retry Logic** | Stay on same level, get new exercise on failure | ✅ |
| 🖥️ **Terminal UI** | Beautiful banners, progress bars, and clean output | ✅ |
| 📁 **Auto Workspace** | Generated `rendu/` and `trace/` directories | ✅ |
| 🏅 **Certificate** | ASCII completion certificate on 100/100 | ✅ |
| ⚡ **Zero Dependencies** | Pure C and Make — nothing else needed | ✅ |

### What Makes It Special

- 🧠 **Anti-Cheat Memory** — Won't give you the same exercise twice in one session
- 🏗️ **Strict Compilation** — Uses `-Wall -Wextra -Werror` just like the real exam
- 📊 **Live Progress** — Watch your score grow as you conquer each level
- 🎨 **Beautiful Terminal** — ASCII art banners and color-coded output
- 🐧 **Unix-Native** — Feels right at home on Linux and macOS

<br>

---

<br>

## ⚡ Requirements

### Minimum Requirements

You need a **Unix-like environment** with just three things:

| Tool | Version | Purpose |
|:-----|:--------|:--------|
| `cc` or `gcc` | Any recent | C compiler |
| `make` | GNU Make 3.81+ | Build system |
| `terminal` | Any | User interface |

### Supported Platforms

- ✅ **Linux** (Ubuntu, Debian, Fedora, Arch, etc.)
- ✅ **macOS** (Intel & Apple Silicon)
- ⚠️ **Windows** (via WSL2 only — native Windows not supported)

### What You DON'T Need

```
❌ No external libraries
❌ No package managers (npm, pip, etc.)
❌ No internet connection after clone
❌ No IDE or text editor (use nano, vim, emacs, or whatever you prefer)
```

> 💡 **Pro Tip:** The simulator is designed to work exactly like the real 42 exam environment. If you can run it, you're ready for the real thing.

<br>

---

<br>

## 🚀 Quick Start

### 1. Clone the Repository

```bash
git clone <repo-url>
cd piscine-simulator
```

### 2. Build

```bash
make
```

You should see output like:

```
cc -Wall -Wextra -Werror -I include -c src/core/main.c -o obj/core/main.o
cc -Wall -Wextra -Werror -I include -c src/engine/exam.c -o obj/engine/exam.o
...
cc -Wall -Wextra -Werror obj/*.o -o piscine-simulator
✅ Build complete: ./piscine-simulator
```

### 3. Run

```bash
./piscine-simulator
```

### One-Liner

```bash
make run
```

<br>

---

<br>

## 🎮 How To Use

### Main Menu

When you start the simulator, you'll see the main menu:

```
╔═══════════════════════════════════════════════════════════════════════════════╗
║                                                                               ║
║                    🏊  PISCINE SIMULATOR v1.0.0  🏊                           ║
║                                                                               ║
╠═══════════════════════════════════════════════════════════════════════════════╣
║                                                                               ║
║   Select your exam:                                                           ║
║                                                                               ║
║      [1] 📝  Start Exam 00  ──  8 levels  ──  4 hours                         ║
║      [2] 📝  Start Exam 01  ──  8 levels  ──  4 hours                         ║
║      [3] 📝  Start Exam 02  ──  8 levels  ──  4 hours                         ║
║      [4] 📝  Start Exam 03  ──  16 levels ──  8 hours                         ║
║                                                                               ║
║      [0] 🚪  Exit                                                             ║
║                                                                               ║
╚═══════════════════════════════════════════════════════════════════════════════╝

Choice: _
```

### During the Exam

After selecting an exam, the simulator presents your exercise:

```
╔═══════════════════════════════════════════════════════════════════════════════╗
║  📋 EXERCISE: aff_a                                                           ║
╠═══════════════════════════════════════════════════════════════════════════════╣
║                                                                               ║
║  Assignment name  : aff_a                                                     ║
║  Expected files   : aff_a.c                                                   ║
║  Allowed functions: write                                                     ║
║                                                                               ║
║  --------------------------------------------------------------------------------
║  Write a program that takes a string and displays the first 'a' character     ║
║  it encounters in it, followed by a newline. If there are no 'a' characters   ║
║  in the string, the program just writes a newline.                            ║
║                                                                               ║
╠═══════════════════════════════════════════════════════════════════════════════╣
║  📁 Put your code in: ./rendu/aff_a/                                          ║
║                                                                               ║
║  🎮 Commands:  test  |  submit  |  exit                                       ║
║                                                                               ║
╚═══════════════════════════════════════════════════════════════════════════════╝
```

### Writing Your Solution

Create your source file in the designated folder:

```bash
# Create the exercise directory
mkdir -p rendu/aff_a

# Write your solution (use your preferred editor)
nano rendu/aff_a/aff_a.c
vim rendu/aff_a/aff_a.c
code rendu/aff_a/aff_a.c   # VS Code
```

### Available Commands

Once back at the simulator prompt, use these commands:

| Command | What It Does | When To Use |
|:--------|:-------------|:------------|
| `test` | Compiles your code with `-Wall -Wextra -Werror` | Check if your code compiles before submitting |
| `submit` | Compiles and validates your attempt | When you're confident your solution is correct |
| `exit` | Quits the simulator immediately | If you need to stop practicing |

<br>

---

<br>

## ✅ Validation Flow

### Step-by-Step Process

For every exercise attempt, the simulator performs the following:

```
┌─────────────────────────────────────────────────────────────────────────────┐
│  STEP 1  │  Create workspace directories                                    │
│          │  ./rendu/<exercise_name>/  &  ./trace/                           │
├─────────────────────────────────────────────────────────────────────────────┤
│  STEP 2  │  Scan for source files                                           │
│          │  Search all *.c files in rendu/<exercise_name>/                  │
├─────────────────────────────────────────────────────────────────────────────┤
│  STEP 3  │  Compile with strict flags                                       │
│          │  cc -Wall -Wextra -Werror ./rendu/<ex>/*.c -o /tmp/ex_out        │
├─────────────────────────────────────────────────────────────────────────────┤
│  STEP 4  │  Evaluate result                                                 │
│          │  ✅ Success → Score up, next level                               │
│          │  ❌ Failure → Save errors to trace/, stay on level               │
└─────────────────────────────────────────────────────────────────────────────┘
```

### Compilation Details

```bash
# The exact compilation command used by the simulator
cc -Wall -Wextra -Werror ./rendu/<exercise_name>/*.c -o /tmp/ex_out
```

| Flag | Meaning |
|:-----|:--------|
| `-Wall` | Enable all common warnings |
| `-Wextra` | Enable extra warnings not covered by `-Wall` |
| `-Werror` | Treat all warnings as errors (strict mode) |

### Result Handling

| Outcome | Behavior |
|:--------|:---------|
| ✅ **Compilation Success** | Exercise marked as passed. Score increases. Level advances. |
| ❌ **Compilation Error** | Errors written to `trace/<exercise_name>.trace`. Score unchanged. New exercise from same level. |
| ⚠️ **No Source Files** | Error message displayed. No penalty. |

<br>

---

<br>

## 📊 Exam Rules

### Exam Comparison

| Property | Exam 00 | Exam 01 | Exam 02 | Exam 03 |
|:---------|:-------:|:-------:|:-------:|:-------:|
| **Levels** | 8 | 8 | 8 | 16 |
| **Exercises per Level** | 6 | 6 | 6 | 6 |
| **Normal Level Points** | 12 | 12 | 12 | 6 |
| **Final Level Points** | 16 | 16 | 16 | 10 |
| **Duration** | 4 hours | 4 hours | 4 hours | 8 hours |
| **Difficulty** | Beginner | Easy | Intermediate | Advanced |

### Scoring System

```
╔═══════════════════════════════════════════════════════════════════════════════=╗
║  🏁 TARGET SCORE:  100 / 100                                                   ║
╠═══════════════════════════════════════════════════════════════════════════════=╣
║                                                                                ║
║  Level 1  ──▶  12 pts    ████░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░  12%  ║
║  Level 2  ──▶  12 pts    ████████░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░  24% ║
║  Level 3  ──▶  12 pts    ████████████░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░  36%║
║  Level 4  ──▶  12 pts    ████████████████░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░  48% ║
║  Level 5  ──▶  12 pts    ████████████████████░░░░░░░░░░░░░░░░░░░░░░░░░░░  60%  ║
║  Level 6  ──▶  12 pts    ████████████████████████░░░░░░░░░░░░░░░░░░░░░░░  72%  ║
║  Level 7  ──▶  12 pts    ████████████████████████████░░░░░░░░░░░░░░░░░░░░  84% ║
║  Level 8  ──▶  16 pts    ████████████████████████████████░░░░░░░░░░░░░░░░░ 100%║
║                                                                                ║
╚═══════════════════════════════════════════════════════════════════════════════=╝
```

### Success vs Failure

#### ✅ On Success

```
┌─────────────────────────────────────────────────────────────┐
│  ✅ EXERCISE PASSED!                                         │
│                                                             │
│  Score:     12 / 100  ──▶  24 / 100                         │
│  Level:     Level 1   ──▶  Level 2                          │
│  Status:    UNLOCKED                                        │
│                                                             │
│  Next exercise pool loaded...                               │
└─────────────────────────────────────────────────────────────┘
```

#### ❌ On Failure

```
┌─────────────────────────────────────────────────────────────┐
│  ❌ EXERCISE FAILED                                          │
│                                                             │
│  Score:     12 / 100  ──▶  12 / 100  (no change)            │
│  Level:     Level 1   ──▶  Level 1   (stay)                 │
│                                                             │
│  New exercise selected from current level...                │
│  Check trace/aff_a.trace for compilation errors.            |
└─────────────────────────────────────────────────────────────┘
```

<br>

---

<br>

## 🔧 Make Commands

### Build Commands

| Command | Description | Output |
|:--------|:------------|:-------|
| `make` | Build the simulator binary | `./piscine-simulator` |
| `make run` | Build and immediately run | Binary + execution |
| `make re` | Clean and rebuild from scratch | Fresh binary |

### Test Commands

| Command | Description | Output |
|:--------|:------------|:-------|
| `make test` | Build and run test binaries | Test results |

### Clean Commands

| Command | Description | Removes |
|:--------|:------------|:--------|
| `make clean` | Remove object files and test binaries | `obj/`, test executables |
| `make fclean` | Full clean + remove simulator binary | Everything from `clean` + `./piscine-simulator` |

### Command Flow

```
make          ──▶  Compile all .c files ──▶  Link ──▶  ./piscine-simulator
make run      ──▶  make ──▶  ./piscine-simulator
make test     ──▶  Compile tests ──▶  Run tests
make clean    ──▶  rm -f obj/* test_binaries
make fclean   ──▶  make clean ──▶  rm -f piscine-simulator
make re       ──▶  make fclean ──▶  make
```

<br>

---

<br>

## 🗂️ Project Structure

```
📦 piscine-simulator/
│
├── 📁 data/                          # Exercise subject files
│   ├── 📁 exam00/                    # 60 exercises for Exam 00
│   │   ├── level01/
│   │   ├── level02/
│   │   ├── ...
│   │   └── level08/
│   ├── 📁 exam01/                    # 60 exercises for Exam 01
│   ├── 📁 exam02/                    # 60 exercises for Exam 02
│   └── 📁 exam03/                    # 60 exercises for Exam 03
│
├── 📁 include/                       # Header files
│   ├── simulator.h                   # Main project header
│   ├── engine.h                      # Exam engine definitions
│   ├── ui.h                          # Terminal UI functions
│   └── utils.h                       # Utility macros
│
├── 📁 src/                           # Source code
│   ├── 📁 core/                      # Entry point & initialization
│   │   └── main.c
│   ├── 📁 engine/                    # Exam logic & state machine
│   │   ├── exam.c
│   │   ├── level.c
│   │   └── scoring.c
│   ├── 📁 io/                        # File I/O operations
│   │   ├── reader.c
│   │   └── writer.c
│   ├── 📁 logic/                     # Validation & compilation
│   │   ├── validator.c
│   │   └── compiler.c
│   ├── 📁 ui/                        # Terminal interface & banners
│   │   ├── banner.c
│   │   ├── menu.c
│   │   └── progress.c
│   └── 📁 utils/                     # Helper functions
│       ├── string_utils.c
│       ├── memory.c
│       └── random.c
│
├── 📁 tests/                         # Unit tests
│   ├── test_engine.c
│   ├── test_validator.c
│   └── test_utils.c
│
├── 📄 makefile                       # Build configuration
├── 📄 README.md                      # This file
└── 🚫 .gitignore                     # Git ignore rules
```

### Runtime Directories (Generated)

```
📁 rendu/                             # Your solutions go here
│   └── 📁 <exercise_name>/
│       └── 📄 <exercise_name>.c
│
📁 trace/                             # Compilation logs
│   └── 📄 <exercise_name>.trace
```

<br>

---

<br>

## 🐛 Troubleshooting

### Common Issues

#### ❌ `make: cc: Command not found`

**Problem:** C compiler not installed or not in PATH.

**Solution:**
```bash
# Ubuntu/Debian
sudo apt-get install build-essential

# Fedora
sudo dnf install gcc make

# macOS
xcode-select --install
```

#### ❌ `data/ directory not found`

**Problem:** The `data/` folder is missing or not in the correct location.

**Solution:** Ensure `data/` is in the same directory as the `piscine-simulator` binary:
```bash
ls -la data/
# Should show: exam00/ exam01/ exam02/ exam03/
```

#### ❌ `Permission denied: ./piscine-simulator`

**Solution:**
```bash
chmod +x ./piscine-simulator
./piscine-simulator
```

#### ⚠️ `Warning: no .c files found in rendu/...`

**Problem:** You haven't created the source file yet, or it's in the wrong place.

**Solution:**
```bash
# Make sure your file is inside the correct rendu/ subdirectory
ls rendu/<exercise_name>/
# Should show: <exercise_name>.c
```

#### ❌ Compilation fails with `-Werror`

**Problem:** Your code has warnings that are treated as errors.

**Solution:** Fix all warnings. This is intentional — the real 42 exam uses the same strict flags.

<br>

---

<br>

## 📝 Notes

> ⚠️ **Important reminders before you start:**

1. 📂 **Keep `data/` next to the binary** — The simulator looks for exercise subjects relative to its executable location.

2. 📁 **Solutions go ONLY in `rendu/`** — Never place your `.c` files outside the `rendu/<exercise_name>/` directory.

3. 📄 **`trace/` is for debugging** — Check this folder when compilation fails to see the exact error messages.

4. 🎲 **No repeats in one session** — The simulator remembers which exercises you've already seen and won't give them to you again until you restart.

5. ⏱️ **Timer is real** — The exam timer runs continuously. If time runs out, the exam ends automatically.

6. 🚫 **Not an official tool** — This is a **practice simulator** for educational purposes. It is not affiliated with, endorsed by, or connected to 42 / 1337 in any official capacity.

7. 💾 **Save your work** — The simulator does not back up your `rendu/` folder. Use `git` or copy your solutions if you want to keep them.

<br>

---

<br>

## 🤝 Contributing

Contributions are welcome! If you'd like to improve the simulator:

1. 🍴 Fork the repository
2. 🌿 Create a feature branch (`git checkout -b feature/amazing-feature`)
3. ✍️ Commit your changes (`git commit -m 'Add amazing feature'`)
4. 📤 Push to the branch (`git push origin feature/amazing-feature`)
5. 🔁 Open a Pull Request

### Ideas for Contributions

- 🌍 Add more exercise subjects
- 🎨 Improve terminal UI / banners
- 🐛 Fix bugs or edge cases
- 📖 Improve documentation
- 🧪 Add more unit tests
- 🖥️ Add support for additional platforms

<br>

---

<br>

## 📜 License

This project is released under the **MIT License**.

```
MIT License

Copyright (c) 2026 Piscine Simulator Contributors

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
```

<br>

---

<br>

<div align="center">

<pre>
╔═══════════════════════════════════════════════════════════════════════════════╗
║                                                                               ║
║              🏊  READY TO DIVE IN?  🏊                                        ║
║                                                                               ║
║                    make && ./piscine-simulator                                ║
║                                                                               ║
╚═══════════════════════════════════════════════════════════════════════════════╝
</pre>

<br>

**Built with** 💙 **C, Make, and a terminal-first workflow.**

*Not an official 42 / 1337 tool — for educational practice only.*

<br>

⭐ **Star this repo if it helped you practice!** ⭐

</div>
