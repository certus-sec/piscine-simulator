# Piscine Simulator

<p align="center">
  <img src="https://img.shields.io/badge/language-C-00599C?style=for-the-badge&logo=c&logoColor=white" alt="C">
  <img src="https://img.shields.io/badge/build-Makefile-427819?style=for-the-badge&logo=gnu&logoColor=white" alt="Makefile">
  <img src="https://img.shields.io/badge/interface-Terminal-111827?style=for-the-badge&logo=gnometerminal&logoColor=white" alt="Terminal">
  <img src="https://img.shields.io/badge/style-42%20%2F%201337-000000?style=for-the-badge" alt="42 / 1337">
</p>

<p align="center">
  A lightweight terminal exam simulator inspired by the 1337 / 42 piscine environment.
</p>

---

## Overview

Piscine Simulator recreates a 42-style exam flow in the terminal:

- choose an exam from `Exam 00` to `Exam 03`
- receive a random exercise from the current level
- write your solution inside the generated `rendu/` folder
- run `test` to compile your answer
- run `submit` to validate and move forward
- reach `100 / 100` to complete the exam

The simulator includes randomized exercise selection, level progression, score tracking, timers, retry behavior, and a completion certificate.

---

## Features

- 4 exam tracks: `exam00`, `exam01`, `exam02`, `exam03`
- 240 exercise subject files
- random exercise picker per level
- anti-repetition logic during the session
- automatic score progression
- exam timers
- terminal UI with banners and progress output
- generated `rendu/` and `trace/` working folders
- built with plain C and Make

---

## Requirements

You need a Unix-like environment with:

- `cc` or `gcc`
- `make`
- a terminal

No external libraries are required.

---

## Quick Start

Clone the repository and enter it:

```bash
git clone <repo-url>
cd piscine-simulator
```

Build the simulator:

```bash
make
```

Run it:

```bash
./piscine-simulator
```

Or build and run with:

```bash
make run
```

---

## How To Use

When the program starts, select the exam you want to practice:

```text
1. Start Exam 00
2. Start Exam 01
3. Start Exam 02
4. Start Exam 03
0. Exit
Choice:
```

After choosing an exam, the simulator displays the current exercise subject and creates a working directory for your solution:

```text
Put your code in: ./rendu/<exercise_name>/
Commands: test | submit | exit
```

Example:

```text
Put your code in: ./rendu/aff_a/
```

Create the expected C file inside that folder:

```bash
mkdir -p rendu/aff_a
$EDITOR rendu/aff_a/aff_a.c
```

Then return to the simulator prompt and use:

```text
test
```

to compile your solution without submitting it.

Use:

```text
submit
```

to validate the exercise attempt.

Use:

```text
exit
```

to leave the simulator.

---

## Validation Flow

For every exercise attempt, the simulator:

1. creates `./rendu/<exercise_name>/`
2. creates `./trace/`
3. searches for `.c` files inside the exercise folder
4. compiles them with:

```bash
cc -Wall -Wextra -Werror ./rendu/<exercise_name>/*.c -o /tmp/ex_out
```

If compilation succeeds, the attempt is treated as successful. Compilation errors are written to the matching file inside `trace/`.

---

## Exam Rules

| Exam | Levels | Exercises per level | Normal level points | Final level points | Duration |
| --- | ---: | ---: | ---: | ---: | ---: |
| Exam 00 | 8 | 6 | 12 | 16 | 4 hours |
| Exam 01 | 8 | 6 | 12 | 16 | 4 hours |
| Exam 02 | 8 | 6 | 12 | 16 | 4 hours |
| Exam 03 | 16 | 6 | 6 | 10 | 8 hours |

Target score:

```text
100 / 100
```

On success:

- your score increases
- the next level is unlocked
- a new exercise pool becomes available

On failure:

- your score stays unchanged
- you stay on the same level
- another exercise from the same level may be selected

---

## Make Commands

| Command | Description |
| --- | --- |
| `make` | Build the simulator |
| `make run` | Build and run the simulator |
| `make test` | Build and run the test binaries |
| `make clean` | Remove object files and test binaries |
| `make fclean` | Remove build output and the simulator binary |
| `make re` | Rebuild from scratch |

---

## Project Structure

```text
piscine-simulator/
├── data/
│   ├── exam00/
│   ├── exam01/
│   ├── exam02/
│   └── exam03/
├── include/
├── src/
│   ├── core/
│   ├── engine/
│   ├── io/
│   ├── logic/
│   ├── ui/
│   └── utils/
├── tests/
├── makefile
└── README.md
```

---

## Notes

- Keep the `data/` directory next to the binary when running the simulator.
- Exercise solutions should be placed only inside `rendu/<exercise_name>/`.
- The `trace/` directory is used for compilation output.
- The project is intended for practice and simulation, not as an official 42 / 1337 exam tool.

---

<p align="center">
  Built with C, Make, and a terminal-first workflow.
</p>
