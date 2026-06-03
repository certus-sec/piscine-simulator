# 🖥️ Piscine Simulator

A terminal-based exam simulator inspired by the 1337 / 42 School exam environment.

Piscine Simulator recreates the progression system of the exams by using levels, randomized exercises, score tracking, and automatic progression through difficulty tiers.

The objective is simple:

**Start at Level 0 and reach 100/100.**

---

## ✨ Features

* 4 different exams
* Randomized exercise selection
* Multiple difficulty levels
* Score progression system
* Anti-repetition exercise engine
* Terminal User Interface (TUI)
* ASCII certificate upon completion
* Lightweight and fast
* Built entirely in C

---

## 🎯 Exam System

### Exam 00

* 8 Levels
* 6 Exercises per level
* 12 Points per completed level
* Final level worth 16 Points

### Exam 01

* 8 Levels
* 6 Exercises per level
* 12 Points per completed level
* Final level worth 16 Points

### Exam 02

* 8 Levels
* 6 Exercises per level
* 12 Points per completed level
* Final level worth 16 Points

### Exam 03

* 16 Levels
* 6 Exercises per level
* 6 Points per completed level
* Final level worth 10 Points

---

## 📈 Progression Rules

### Success

When an exercise is completed successfully:

* Score is updated
* Next level is unlocked
* New exercise pool becomes available

### Failure

When an exercise fails:

* A different exercise from the same level is selected
* The current level remains unchanged
* The score is not modified

---

## 🧠 Exercise Engine

Each level contains:

```text
6 Exercises
```

The simulator:

* Randomly selects an exercise
* Prevents duplicates during the same session
* Tracks progression
* Updates score automatically

---

## 🏆 Completion

When the user reaches:

```text
100 / 100
```

The simulator generates a terminal certificate displaying:

* Username
* Exam completed
* Final score
* Completion date

---

## 📂 Project Structure

```text
piscine-simulator/
│
├── Makefile
├── README.md
│
├── include/
│
├── src/
│   ├── engine/
│   ├── logic/
│   ├── ui/
│   ├── io/
│   └── utils/
│
├── data/
│   ├── exam00/
│   ├── exam01/
│   ├── exam02/
│   └── exam03/
│
└── tests/
```

---

## 🚀 Build

```bash
make
```

Run:

```bash
./simulator
```

---

## 📜 Example

```text
========================================
        PISCINE SIMULATOR
========================================

[1] Exam 00
[2] Exam 01
[3] Exam 02
[4] Exam 03

Choice >
```

---

## 🏅 Goal

Piscine Simulator is designed to help students:

* Practice under pressure
* Improve problem-solving speed
* Build consistency
* Prepare for 1337 / 42 style exams

---

<p align="center">
  Built with C • Terminal Driven • Inspired by 1337/42
</p>
