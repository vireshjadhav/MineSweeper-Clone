# 🎮 Minesweeper (Console Version)

## 📌 Overview

This project is a console-based implementation of the classic Minesweeper game, developed using C++ and Object-Oriented Programming (OOP) principles.

The game allows players to uncover cells, flag potential mines, and strategically clear the board without triggering a mine — all within a limited time.

---

## 🚀 Features

* Multiple difficulty levels:

  * Beginner (9×9, 10 mines, 600 sec)
  * Intermediate (16×16, 40 mines, 900 sec)
  * Expert (21×21, 90 mines, 1200 sec)
* Countdown timer system ⏱
* First-click safety (first move never hits a mine)
* Recursive cell reveal (auto-expansion of empty cells)
* Flag and unflag system
* Input validation for safe gameplay
* Dynamic board display after every move
* Restart system after game ends
* Quit option during gameplay (Q)
* Win/Lose detection (mine hit or time expired)

---

## 🎮 How to Play

### Controls (Two-Step Input System)

Step 1: Enter Action

```
O → Open a cell  
F → Flag / Unflag a cell  
Q → Quit the game  
```

Step 2: Enter Position (only for O and F)

```
Row Column
```

### Examples

```
O
2 3     → Open cell at (2, 3)

F
4 5     → Toggle flag at (4, 5)

Q       → Quit the game
```

---

## 📜 Game Rules

* The board contains hidden mines.
* Opening a mine results in game over.
* Numbers indicate how many mines are adjacent to that cell.
* Open all non-mine cells to win the game.
* The game must be completed before the timer runs out.

---

## 🧠 Game Logic Highlights

### First Click Safety

* Mines are generated after the first move
* Ensures the first clicked cell is always safe

### Recursive Reveal

* Empty cells automatically reveal neighboring cells
* Expansion stops at numbered cells

### Timer System

* Countdown timer based on difficulty
* Timer runs continuously during gameplay
* Time reaching zero results in a loss

---

## 🏗️ Project Structure

```
N_Utility   → Helper functions (console, input handling)
N_UI        → Console-based UI and user interaction (ConsoleUI)
N_Game      → Core game logic
    ├── Cell
    ├── Board
    ├── Gameplay
    └── Timer
```

---

## 🧩 OOP Concepts Used

* Encapsulation (Cell, Board classes)
* Abstraction (Game logic hidden behind methods)
* Modular design (separate namespaces)
* Dynamic memory management

---

## ⚙️ How to Run

### Compile:

```
g++ main.cpp -o minesweeper
```

### Run:

```
./minesweeper
```

---

## ✨ Future Improvements

* Color-coded numbers in console
* Pause / Resume functionality
* High score tracking 🏆
* Custom difficulty settings
* GUI version using Unity or Unreal 🎮
* Sound effects 🔊

---

## 👨‍💻 Author

**Viresh Jadhav**

---

## 📌 Notes

This project was built as part of a structured assignment to improve:

* Problem-solving skills
* OOP design thinking
* Game logic implementation

---

⭐ If you like this project, consider giving it a star!
