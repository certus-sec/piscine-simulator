<div align="center">

[![capsule](https://capsule-render.vercel.app/api?type=waving&color=0:0f172a,50:1e3a5f,100:0D4AA&height=200&section=header&text=Piscine%20Simulator&fontSize=52&fontColor=ffffff&fontAlignY=38&desc=Train%20Under%20Real%2042%20%2F%201337%20Exam%20Conditions&descAlignY=58&descSize=18&animation=fadeIn)](https://github.com/certus-sec/piscine-simulator)

[![Typing SVG](https://readme-typing-svg.herokuapp.com?font=Fira+Code&weight=700&size=22&duration=3000&pause=1000&color=00D4AA&center=true&vCenter=true&width=600&lines=Terminal-based+Exam+Simulator;Built+in+Pure+C+%7C+Zero+Dependencies;240%2B+Exercises+Across+4+Exams;Practice.+Fail.+Learn.+Repeat.)](https://github.com/certus-sec/piscine-simulator)

<br/>

[![Language](https://img.shields.io/badge/Language-C-00599C?style=for-the-badge&logo=c&logoColor=white)](https://github.com/certus-sec/piscine-simulator)
[![Build](https://img.shields.io/badge/Build-Makefile-427819?style=for-the-badge&logo=gnu&logoColor=white)](https://github.com/certus-sec/piscine-simulator)
[![Platform](https://img.shields.io/badge/Platform-Linux%20%7C%20macOS-8b5cf6?style=for-the-badge&logo=linux&logoColor=white)](https://github.com/certus-sec/piscine-simulator)
[![Dependencies](https://img.shields.io/badge/Dependencies-None-f59e0b?style=for-the-badge)](https://github.com/certus-sec/piscine-simulator)
[![License](https://img.shields.io/badge/License-MIT-22c55e?style=for-the-badge)](https://github.com/certus-sec/piscine-simulator/blob/main/LICENSE)

</div>

---

## 📊 At a Glance

<div align="center">

| 📋 Metric | 🔢 Value |
|:---------:|:--------:|
| 🏫 Exams | **4** |
| 📊 Levels | **40** |
| 📝 Exercises | **240+** |
| 💻 Language | **C** |
| 📦 Dependencies | **0** |
| 🖥️ Platforms | **Linux / macOS** |

</div>

---

## 🎯 Overview

**Piscine Simulator** replicates the authentic **1337 / 42** Piscine exam environment, letting students practice under real exam conditions — timed sessions, grademe penalties, molinette feedback, and auto progression.

```
  Exam00  ──►  Exam01  ──►  Exam02  ──►  Exam03
  [ L0–L7 ]    [ L0–L7 ]    [ L0–L7 ]    [ L0–L15 ]
```

---

## 🚀 Quick Start

```bash
git clone https://github.com/certus-sec/piscine-simulator.git
cd piscine-simulator
make
./piscine-simulator
```

---

## ✨ Features

<div align="center">

| 🎓 Exam System | 🚀 User Experience |
|:---|:---|
| ✅ 4 Progressive Exam Tracks | ✅ Beautiful Terminal UI |
| ✅ 240+ Exercises | ✅ Live Progress Bars |
| ✅ Smart Randomization | ✅ Auto Workspace Setup |
| ✅ Realistic Countdown Timers | ✅ Completion Certificate |
| ✅ Auto Level Progression | ✅ Zero Dependencies |
| ✅ Molinette-style Feedback | ✅ Error Logs in `./trace/` |

</div>

---

## 📸 Preview

<p align="center">
  <img src="https://github.com/certus-sec/piscine-simulator/blob/main/data/banner.png?raw=true" width="780" alt="Piscine Simulator Preview"/>
</p>

---

## ⚡ Requirements

<details>
<summary><b>🐧 Ubuntu / Debian</b></summary>

```bash
sudo apt install build-essential
```

</details>

<details>
<summary><b>🎩 Fedora / RHEL</b></summary>

```bash
sudo dnf install gcc make
```

</details>

<details>
<summary><b>🍎 macOS</b></summary>

```bash
xcode-select --install
```

</details>

---

## 🔧 Build Commands

<div align="center">

| Command | Description |
|:--------|:------------|
| `make` | Build the project |
| `make run` | Build & Run immediately |
| `make test` | Run test suite |
| `make clean` | Remove object files |
| `make fclean` | Full clean (binaries + objects) |
| `make re` | Full rebuild from scratch |

</div>

---

## 🎮 How To Use

```
1.  Launch        →  ./piscine-simulator
2.  Select Exam   →  Choose Exam00 through Exam03
3.  Read Subject  →  Subject displayed in terminal
4.  Write Code    →  ./rendu/<exercise_name>/
5.  Test          →  type: test
6.  Submit        →  type: gradme
7.  Pass Level    →  Score updates, next level unlocks
8.  Reach 100     →  Certificate generated 🎓
```

---

## 📊 Exam Rules

### 🏆 Scoring

<div align="center">

| Level | Points |
|:-----:|:------:|
| Levels 1 – 7 | **12 pts each** |
| Level 8 | **16 pts** |
| 🎯 Target | **100 / 100** |

</div>

### ⏳ Grademe Penalties

<div align="center">

| Attempt | ⏱️ Wait Time |
|:-------:|:-----------:|
| 1st | 10 min |
| 2nd | 20 min |
| 3rd | 40 min |
| 4th+ | 1 hour |

</div>

---

## 🐛 Molinette Feedback

When your submission fails, the simulator saves a detailed error report:

```bash
./trace/<exercise>_molinette.log
```

**Compilation errors:**
```
=== MOLINETTE REPORT: aff_z ===
Status : COMPILATION FAILED

--- Compiler Errors ---
aff_z.c:5:3: error: use of undeclared identifier 'write'
```

**Test failures:**
```
=== MOLINETTE REPORT: aff_z ===
Passed : 1 / 3
Failed : 2 / 3

--- Test Details ---
✓ PASS: aff_z "zoo" -> 'z'
✗ FAIL: aff_z "abc" -> ''
  Expected: ''
  Got:      'z'
```

---

## 🗂️ Project Structure

```
piscine-simulator/
├── 📁 src/
│   ├── engine/        ←  Core exam runner & grading logic
│   ├── grader/        ←  Molinette-style test system
│   ├── core/          ←  Exam / level / exercise models
│   ├── logic/         ←  Progression, retry, scoring
│   ├── ui/            ←  Terminal display & certificate
│   ├── io/            ←  File reader & input handler
│   └── utils/         ←  Memory, strings, time helpers
├── 📁 include/        ←  Header files
├── 📁 data/           ←  Exercise subjects (exam00–exam03)
├── 📁 tests/          ←  Test suite
├── 📁 build/          ←  Compiled objects
├── 📁 rendu/          ←  Your code goes here (auto-created)
├── 📁 trace/          ←  Molinette logs (auto-created)
└── 📄 makefile
```

---

## 🤝 Contributing

```bash
# Fork → Clone → Branch → Commit → PR
git checkout -b feature/my-feature
git commit -m "feat: add my feature"
git push origin feature/my-feature
```

---

## 📜 License

Distributed under the **MIT License**.

---

<div align="center">

[![wave](https://capsule-render.vercel.app/api?type=waving&color=0:0D4AA,50:1e3a5f,100:0f172a&height=120&section=footer)](https://github.com/certus-sec/piscine-simulator)

**Built for 42 / 1337 Students**

*Practice. Fail. Learn. Repeat.*

⭐ Star the project if it helped you — it means a lot!

[![GitHub](https://img.shields.io/badge/GitHub-certus--sec-181717?style=flat&logo=github&logoColor=white)](https://github.com/certus-sec)
[![LinkedIn](https://img.shields.io/badge/LinkedIn-certus--sec-0077B5?style=flat&logo=linkedin&logoColor=white)](https://linkedin.com/in/certus-sec)
[![X](https://img.shields.io/badge/X-certus__sec-000000?style=flat&logo=x&logoColor=white)](https://x.com/certus_sec)

</div>
