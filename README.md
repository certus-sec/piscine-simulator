<img src ="https://capsule-render.vercel.app/api?type=waving&color=0:0a0a0a,50:1a1a2e,100:16213e&height=200&section=header&fontColor=00d4ff&text=PISCINE%20SIMULATOR&fontSize=90&fontFamily=JetBrains%20Mono&animation=fadeIn" width="100%"/>

<div align="center">

[![typing](https://readme-typing-svg.demolab.com?font=JetBrains+Mono&weight=600&size=18&duration=3000&pause=800&color=00d4ff&center=true&vCenter=true&multiline=false&width=600&lines=🏊+42%2F1337+Piscine+Exam+Simulator;Practice+like+a+pro+before+the+real+exam;Terminal+based+%7C+Pure+C+%7C+Zero+Dependencies)](https://github.com/certus-sec/piscine-simulator)

</div>

---

<div align="center">

## 🎓 Project Badges

[![Language](https://img.shields.io/badge/language-C-00599C?style=for-the-badge&logo=c&logoColor=white&labelColor=0d0d0d)](https://github.com/certus-sec/piscine-simulator)
[![Build](https://img.shields.io/badge/build-Makefile-427819?style=for-the-badge&logo=gnu&logoColor=white&labelColor=0d0d0d)](https://github.com/certus-sec/piscine-simulator)
[![Interface](https://img.shields.io/badge/interface-Terminal-111827?style=for-the-badge&logo=gnometerminal&logoColor=white&labelColor=0d0d0d)](https://github.com/certus-sec/piscine-simulator)
[![License](https://img.shields.io/badge/license-MIT-10b981?style=for-the-badge&logoColor=white&labelColor=0d0d0d)](./LICENSE)

[![Version](https://img.shields.io/badge/version-1.0.0-06b6d4?style=flat&logo=github&labelColor=0d0d0d)](https://github.com/certus-sec/piscine-simulator)
[![Platform](https://img.shields.io/badge/platform-Linux%20%7C%20macOS-8b5cf6?style=flat&labelColor=0d0d0d)](https://github.com/certus-sec/piscine-simulator)
[![Dependencies](https://img.shields.io/badge/dependencies-none-f59e0b?style=flat&labelColor=0d0d0d)](https://github.com/certus-sec/piscine-simulator)
[![Style](https://img.shields.io/badge/code%20style-42%20%2F%201337-000000?style=flat&labelColor=0d0d0d)](https://github.com/certus-sec/piscine-simulator)

</div>

---

## 📋 Table of Contents

- [🎯 Overview](#-overview)
- [✨ Features](#-features)
- [⚡ Requirements](#-requirements)
- [🚀 Quick Start](#-quick-start)
- [🎮 How To Use](#-how-to-use)
- [✅ Validation Flow](#-validation-flow)
- [📊 Exam Rules](#-exam-rules)
- [🔧 Build Commands](#-build-commands)
- [🗂️ Project Structure](#-project-structure)
- [🐛 Troubleshooting](#-troubleshooting)
- [🤝 Contributing](#-contributing)
- [📜 License](#-license)

---

## 🎯 Overview

**Piscine Simulator** is a terminal-based exam environment designed to replicate the authentic **1337 / 42 Piscine** experience. It provides students with a realistic practice platform to solve C programming exercises under exam conditions.

<div align="center">

┌─────────────────────────────────────────────────────────────────┐ │ │ │ ┌──────────┐ ┌──────────┐ ┌──────────┐ ┌──────────┐ │ │ │ Exam 00 │───▶│ Exam 01 │───▶│ Exam 02 │───▶│ Exam 03 │ │ │ └──────────┘ └──────────┘ └──────────┘ └──────────┘ │ │ │ │ │ │ │ │ ▼ ▼ ▼ ▼ │ │ ┌─────────────────────────────────────────────────────────┐ │ │ │ Level 01 → Level 02 → ... → Level 08 / 16 │ │ │ │ (Random exercise pool per level) │ │ │ └─────────────────────────────────────────────────────────┘ │ │ 🏁 TARGET: 100 / 100 │ │ │ └─────────────────────────────────────────────────────────────────┘
Code


</div>

### 📊 Exam Structure

| Exam | Levels | Difficulty | Duration | Total Exercises |
|:----:|:------:|:----------:|:--------:|:---------------:|
| **Exam 00** | 8 | Beginner | 4h | 48 |
| **Exam 01** | 8 | Easy | 4h | 48 |
| **Exam 02** | 8 | Intermediate | 4h | 48 |
| **Exam 03** | 16 | Advanced | 8h | 96 |

---

## ✨ Features

<table width="100%">
<tr>
<td width="50%">

### 🎓 Core Functionality
- ✅ **4 Exam Tracks** with progressive difficulty
- ✅ **240+ Exercises** covering C fundamentals
- ✅ **Smart Randomization** (no repeats per session)
- ✅ **Auto Progression** with level unlocking
- ✅ **Realistic Timers** (4h and 8h exams)
- ✅ **Retry Logic** on failure

</td>
<td width="50%">

### 🚀 User Experience
- ✅ **Beautiful Terminal UI** with ASCII banners
- ✅ **Live Progress Bars** tracking your score
- ✅ **Auto Workspace** (rendu/ & trace/)
- ✅ **Completion Certificate** at 100/100
- ✅ **Strict Compilation** (-Wall -Wextra -Werror)
- ✅ **Zero Dependencies** (Pure C + Make)

</td>
</tr>
</table>

### 🧠 What Makes It Special

• Anti-Cheat Memory → Won't repeat exercises in one session • Exam Authenticity → Mimics real 42 environment exactly • Grademe Penalties → Progressive wait times (10m, 20m, 40m, 1h) • Unix-First Design → Native feel on Linux & macOS • Educational Focus → Learn under realistic exam pressure
Code


---

## ⚡ Requirements

### System Requirements

| Tool | Version | Purpose |
|:-----|:--------|:--------|
| **C Compiler** | gcc/clang | Compile source code |
| **GNU Make** | 3.81+ | Build system |
| **Terminal** | Any | User interface |
| **OS** | Linux/macOS | Execution environment |

### What You DON'T Need

❌ No external libraries ❌ No package managers (npm, pip, etc.) ❌ No internet after clone ❌ No IDE (use nano, vim, or your editor)
Code


<details>
<summary><strong>🔧 Install Compiler</strong></summary>

```bash
# Ubuntu / Debian
sudo apt-get update && sudo apt-get install build-essential

# Fedora / RHEL
sudo dnf install gcc make

# macOS
xcode-select --install

</details>
🚀 Quick Start
1️⃣ Clone Repository
bash

git clone https://github.com/certus-sec/piscine-simulator.git
cd piscine-simulator

2️⃣ Build
bash

make

Expected output:
Code

cc -Wall -Wextra -Werror -I include -c src/main.c -o build/main.o
cc -Wall -Wextra -Werror -I include -c src/engine/exam_engine.c -o build/exam_engine.o
...
cc -Wall -Wextra -Werror build/*.o -o piscine-simulator
✅ Build successful: ./piscine-simulator

3️⃣ Run
bash

./piscine-simulator

⚡ One-Liner
bash

make && ./piscine-simulator

🎮 How To Use
Main Menu
Code

╔═══════════════════════════════════════════════════════════╗
║                                                           ║
║           🏊 PISCINE SIMULATOR v1.0.0 🏊                 ║
║                                                           ║
╠═══════════════════════════════════════════════════════════╣
║                                                           ║
║  Select your exam:                                        ║
║                                                           ║
║     [1] 📝  Start Exam 00  ──  8 levels  ──  4 hours      ║
║     [2] 📝  Start Exam 01  ──  8 levels  ──  4 hours      ║
║     [3] 📝  Start Exam 02  ──  8 levels  ──  4 hours      ║
║     [4] 📝  Start Exam 03  ──  16 levels ──  8 hours      ║
║                                                           ║
║     [0] 🚪  Exit                                          ║
║                                                           ║
╚═══════════════════════════════════════════════════════════╝

Choice: _

During Exam
Code

╔═══════════════════════════════════════════════════════════╗
║  📋 EXERCISE: ft_strlen                                  ║
╠═══════════════════════════════════════════════════════════╣
║                                                           ║
║  Assignment:   ft_strlen                                 ║
║  Expected:     ft_strlen.c                               ║
║  Allowed:      strlen, printf                            ║
║                                                           ║
║  ─────────────────────────────────────────────────────    ║
║  Write a function that returns the length of a string   ║
║  Do not use the original strlen function.               ║
║                                                           ║
╠═══════════════════════════════════════════════════════════╣
║  📁 Directory: ./rendu/ft_strlen/                        ║
║                                                           ║
║  💻 Commands: test | gradme | exit                       ║
╚═══════════════════════════════════════════════════════════╝

Available Commands
Command	Purpose	Penalty
test	Compile & check for errors	⏱️ None
gradme	Submit solution	⏱️ Progressive wait
exit	Quit immediately	⏱️ End session
✅ Validation Flow
Step-by-Step Process
Code

┌────────────────────────────────────────────────────────┐
│ STEP 1: Create Workspace                               │
│         mkdir -p ./rendu/<exercise>/ ./trace/           │
├────────────────────────────────────────────────────────┤
│ STEP 2: User Writes Code                               │
│         nano/vim/code ./rendu/<exercise>/<name>.c       │
├────────────────────────────────────────────────────────┤
│ STEP 3: Compile with Strict Flags                      │
│         cc -Wall -Wextra -Werror *.c -o /tmp/ex_out    │
├────────────────────────────────────────────────────────┤
│ STEP 4: Evaluate Result                                │
│         ✅ Success → Points up + Next level             │
│         ❌ Failure → Log error + Same level             │
└────────────────────────────────────────────────────────┘

Compilation Flags Explained
Flag	Meaning
-Wall	Enable all common warnings
-Wextra	Enable extra warnings
-Werror	Treat warnings as errors (strict)
Result Handling
Outcome	Behavior
✅ Compilation Success	Score +12pts → Next level
❌ Compilation Error	Saved to trace/ → Same level
⚠️ No Source Files	Error message → No penalty
📊 Exam Rules
Scoring System
<div align="center">
Code

🏁 TARGET SCORE: 100 / 100

Level 1  ──▶  12 pts    ████░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░  12%
Level 2  ──▶  12 pts    ████████░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░  24%
Level 3  ──▶  12 pts    ████████████░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░  36%
Level 4  ──▶  12 pts    ████████████████░░░░░░░░░░░░░░░░░░░░░░░░░░░░  48%
Level 5  ──▶  12 pts    ████████████████████░░░░░░░░░░░░░░░░░░░░░░░░  60%
Level 6  ──▶  12 pts    ████████████████████████░░░░░░░░░░░░░░░░░░░░░  72%
Level 7  ──▶  12 pts    ████████████████████████████░░░░░░░░░░░░░░░░░  84%
Level 8  ──▶  16 pts    ████████████████████████████████░░░░░░░░░░░░░░ 100%

</div>
Success vs Failure
<table width="100%"> <tr> <td width="50%">
✅ On Success
Code

┌─────────────────────────────┐
│ ✅ EXERCISE PASSED!         │
│                             │
│ Score:  12/100  ──▶  24/100 │
│ Level:  01      ──▶  02     │
│ Status: UNLOCKED            │
│                             │
│ Next pool loaded...         │
└─────────────────────────────┘

</td> <td width="50%">
❌ On Failure
Code

┌─────────────────────────────┐
│ ❌ EXERCISE FAILED          │
│                             │
│ Score:  12/100  ──▶  12/100 │
│ Level:  01      ──▶  01     │
│ Status: TRY AGAIN           │
│                             │
│ Check trace/ for errors.    │
└─────────────────────────────┘

</td> </tr> </table>
Grademe Penalty System
Attempt	Wait Time	Impact
1st	10 minutes	Build experience
2nd	20 minutes	Think more carefully
3rd	40 minutes	Reconsider your approach
4th+	1 hour	Deep debugging required
🔧 Build Commands
Core Commands
bash

make              # Build the simulator
make run          # Build and run immediately
make re            # Clean rebuild from scratch
make test         # Build and run unit tests
make clean        # Remove object files and tests
make fclean       # Full clean (remove binary too)

Command Flow Diagram
Code

make          ──▶  Compile .c files  ──▶  Link  ──▶  ./piscine-simulator
make run      ──▶  make  ──▶  ./piscine-simulator
make test     ──▶  Compile tests  ──▶  Run tests
make clean    ──▶  rm -f build/* test_*
make fclean   ──▶  make clean  ──▶  rm -f piscine-simulator
make re       ──▶  make fclean  ──▶  make

🗂️ Project Structure
Code

📦 piscine-simulator/
│
├── 📄 README.md                    # This file
├── 📄 makefile                     # Build configuration
├── 📄 .gitignore                   # Git ignore rules
│
├── 📁 include/                     # Header files
│   ├── simulator.h                 # Main project definitions
│   ├── exam.h                      # Exam structures
│   ├── level.h                     # Level structures
│   ├── exercise.h                  # Exercise structures
│   ├── config.h                    # Configuration
│   └── utils.h                     # Utility functions
│
├── 📁 src/                         # Source code (96.1%)
│   ├── main.c                      # Entry point
│   │
│   ├── 📁 engine/                  # Core Engines
│   │   ├── exam_engine.c           # Exam state management
│   │   ├── level_engine.c          # Level progression
│   │   ├── score_engine.c          # Scoring system
│   │   └── runner.c                # Main game loop
│   │
│   ├── 📁 core/                    # Core Logic
│   │   ├── exam.c                  # Exam initialization
│   │   ├── exercise.c              # Exercise handling
│   │   ├── exercise_loader.c       # Load from disk
│   │   ├── config_loader.c         # Load configuration
│   │   └── level.c                 # Level setup
│   │
│   ├── 📁 logic/                   # Business Logic
│   │   ├── random_picker.c         # Random selection (no repeats)
│   │   ├── validator.c             # Code validation
│   │   ├── retry_system.c          # Retry mechanics
│   │   └── progression.c           # Progress tracking
│   │
│   ├── 📁 ui/                      # User Interface
│   │   ├── banner.c                # ASCII banners
│   │   ├── menu.c                  # Menu system
│   │   ├── display.c               # Output formatting
│   │   ├── progress_bar.c          # Progress visualization
│   │   └── certificate.c           # Completion certificate
│   │
│   ├── 📁 io/                      # Input/Output
│   │   ├── input_handler.c         # User input
│   │   ├── file_reader.c           # Read files
│   │   └── logger.c                # Event logging
│   │
│   └── 📁 utils/                   # Utilities
│       ├── strings.c               # String functions
│       ├── memory.c                # Memory management
│       └── time.c                  # Time utilities
│
├── 📁 tests/                       # Unit Tests
│   ├── test_engine.c               # Engine tests
│   ├── test_levels.c               # Level tests
│   └── test_score.c                # Scoring tests
│
├── 📁 data/                        # Exercise Data
│   ├── banner.png                  # Logo/Banner image
│   ├── 📁 exam00/                  # Exam 00 exercises (60)
│   ├── 📁 exam01/                  # Exam 01 exercises (60)
│   ├── 📁 exam02/                  # Exam 02 exercises (60)
│   └── 📁 exam03/                  # Exam 03 exercises (96)
│
└── 📁 build/                       # Build artifacts (generated)
    └── *.o                         # Object files

Runtime Directories (Auto-Generated)
Code

📁 rendu/                          # Your solutions go here
│   └── 📁 <exercise_name>/
│       └── 📄 <exercise_name>.c
│
📁 trace/                          # Compilation logs
│   └── 📄 <exercise_name>.trace

🐛 Troubleshooting
<details> <summary><strong>❌ cc: Command not found</strong></summary>

Problem: C compiler not installed or not in PATH.

Solution:
bash

# Ubuntu/Debian
sudo apt-get install build-essential

# Fedora
sudo dnf install gcc make

# macOS
xcode-select --install

</details> <details> <summary><strong>❌ data/ directory not found</strong></summary>

Problem: Exercise data folder is missing.

Solution: Ensure data/ is in the same directory as the binary.
bash

ls -la data/
# Should show: exam00/  exam01/  exam02/  exam03/  banner.png

</details> <details> <summary><strong>❌ Permission denied: ./piscine-simulator</strong></summary>

Solution:
bash

chmod +x ./piscine-simulator
./piscine-simulator

</details> <details> <summary><strong>⚠️ No .c files found in rendu/...</strong></summary>

Problem: You haven't created the source file yet.

Solution: Make sure your file is in the correct rendu/ subdirectory.
bash

ls rendu/<exercise_name>/
# Should show: <exercise_name>.c

</details> <details> <summary><strong>❌ Compilation fails with -Werror</strong></summary>

Problem: Your code has warnings treated as errors.

Solution: Fix all warnings. This is intentional—the real 42 exam uses strict flags.
bash

# Check for warnings
cc -Wall -Wextra ./rendu/<exercise>/*.c -o /tmp/test

# Common issues:
# - Unused variables
# - Implicit function declarations
# - Type mismatches

</details>
📝 Important Notes

    ⚠️ Before you start:

    📂 Keep data/ with binary — The simulator finds exercises relative to its location
    📁 Solutions go in rendu/ only — Never place .c files outside the rendu structure
    📄 trace/ is for debugging — Check here when compilation fails
    🎲 No repeats in session — Simulator remembers which exercises you've seen
    ⏱️ Timer runs continuously — Exam ends automatically when time is up
    🚫 Not official — This is educational practice only, not affiliated with 42/1337
    💾 Backup your work — Use Git to save your solutions

🤝 Contributing

Contributions are welcome! Here's how to contribute:
bash

# 1. Fork the repository
# 2. Create a feature branch
git checkout -b feature/awesome-feature

# 3. Make your changes
vim src/your_file.c

# 4. Commit with a clear message
git commit -m "Add awesome feature"

# 5. Push to your fork
git push origin feature/awesome-feature

# 6. Open a Pull Request

Ideas for Contributions

    🌍 Add more exercises to data/
    🎨 Improve terminal UI/banners
    🐛 Bug fixes
    📖 Better documentation
    🧪 More unit tests
    🖥️ Support for other platforms

📜 License

This project is released under the MIT License.
Code

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
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.

<div align="center">
📊 Repository Stats

![GitHub Stars](https://img.shields.io/github/stars/certus-sec/piscine-simulator?style=for-the-badge&label=⭐%20Stars&labelColor=0d0d0d&color=00d4ff) ![GitHub Forks](https://img.shields.io/github/forks/certus-sec/piscine-simulator?style=for-the-badge&label=⎇%20Forks&labelColor=0d0d0d&color=00d4ff) ![Last Commit](https://img.shields.io/github/last-commit/certus-sec/piscine-simulator?style=for-the-badge&label=↑%20Pushed&labelColor=0d0d0d&color=00d4ff&logo=git) ![Repo Size](https://img.shields.io/github/repo-size/certus-sec/piscine-simulator?style=for-the-badge&label=◆%20Size&labelColor=0d0d0d&color=00d4ff)
<p align="center"> <a href="https://github.com/certus-sec"> <img src="https://readme-typing-svg.demolab.com?font=JetBrains+Mono&weight=600&size=18&duration=4000&pause=1000&color=00d4ff&center=true&vCenter=true&width=600&lines=Built+with+💙+C%2C+Make%2C+and+Terminal+magic;Ready+to+practice+like+a+pro%3F" alt="Call to action" /> </a> </p>
🚀 Next Steps
bash

# Clone this repository
git clone https://github.com/certus-sec/piscine-simulator.git
cd piscine-simulator

# Build the simulator
make

# Start practicing!
./piscine-simulator

<p align="center"> <strong>⭐ If this helped you prepare, please star the repo! ⭐</strong> </p> <img src ="https://capsule-render.vercel.app/api?type=waving&color=0:0f172a,100:00d4ff&height=100&section=footer&fontColor=ffffff&animation=fadeIn" width="100%"/> </div> ```
