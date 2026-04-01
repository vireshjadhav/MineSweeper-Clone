# 🎮 Game Design Document (GDD)

## Project: Minesweeper (Console Edition)

---

## 1. 📌 Game Overview

**Genre:** Puzzle / Strategy
**Platform:** Console (C++ CLI Application)
**Target Audience:** Beginners to intermediate players who enjoy logical reasoning games

The game challenges players to clear a grid of hidden mines using logic, deduction, and time management.

---

## 2. 🎯 Objective

* Reveal all non-mine cells
* Avoid triggering any mine
* Use numerical clues to deduce safe cells
* Complete the game before time runs out

---

## 3. 🧩 Core Gameplay Mechanics

### 3.1 Grid System

* Square grid (n × n)
* Minimum size: 9×9
* Each cell contains:

  * Mine OR
  * Number (0–8)

---

### 3.2 Player Actions

| Action   | Description                |
| -------- | -------------------------- |
| O (Open) | Reveals the selected cell  |
| F (Flag) | Toggles flag on a cell     |
| Q (Quit) | Exits the game immediately |

---

### 3.2.1 Input Format

Player input is taken in **two steps**:

**Step 1: Action Input**

`<Action>`

* `O` → Open a cell
* `F` → Toggle flag
* `Q` → Quit the game

---

**Step 2: Position Input (only for O and F)**

`<Row> <Column>`

**Examples:**

* `O` → then `2 3` → Open cell at (2, 3)
* `F` → then `4 5` → Toggle flag at (4, 5)
* `Q` → Game exits immediately (no row/column required)

---

**Notes:**

* Action is always entered first
* Row and Column are required only for `O` and `F`
* `Q` does not require position input

---

### 3.3 First Click Safety

* Mines are generated **after first input**
* First clicked cell is guaranteed safe

---

### 3.4 Cell Behavior

| Cell Type | Behavior                  |
| --------- | ------------------------- |
| Empty (0) | Expands recursively       |
| Number    | Shows adjacent mine count |
| Mine      | Ends game                 |

---

### 3.5 Recursive Expansion

* Empty cells automatically reveal neighbors
* Stops at numbered cells

---

### 3.6 Countdown Timer

* Each game has a fixed time limit based on difficulty:

  * Easy → 600 seconds
  * Medium → 900 seconds
  * Hard → 1200 seconds
* Timer continuously decreases during gameplay
* If time reaches zero → player loses the game

---

## 4. 🎮 Game Flow

1. Display rules and instructions

2. Player selects difficulty

3. Game initializes board and timer

4. Game loop:

   * Display game stats (time left, mines left)
   * Display board
   * Take user input (two-step input system)
   * Update board
   * Check:

     * Win condition
     * Mine trigger
     * Timer expiration

5. End game:

   * Win → All safe cells opened
   * Lose →

     * Mine triggered
     * Timer reached zero

6. Player chooses:

   * Restart game
   * Exit game

---

## 5. 🧠 Game States

* `PLAYING`
* `WON`
* `LOST`

**Note:** Timer expiration results in a loss, not a separate game state.

---

## 6. ⚙️ Technical Design

### 6.1 Core Classes

#### Cell

* Stores:

  * State (Hidden, Open, Flagged)
  * Type (Mine, Number, Empty)

* Handles:

  * Display representation
  * State transitions

---

#### Board

* Handles:

  * Grid creation
  * Mine placement
  * Neighbor calculations
  * Recursive expansion (flood fill)
  * Win condition logic
  * Flag tracking

---

#### Gameplay

* Controls:

  * Main game loop
  * State transitions
  * Timer integration
  * Restart system
  * User interaction flow

---

#### ConsoleUI

* Handles:

  * User input (two-step input handling)
  * Output display
  * HUD rendering (time + mines)
  * Validation messages
  * Restart confirmation

---

#### Timer

* Handles:

  * Countdown logic using `std::chrono`
  * Remaining time calculation
  * Time-up detection

---

## 7. 🧪 Validation & Constraints

* Input must follow two-step format: action first, then position
* Row and column are required only for `O` and `F`
* `Q` does not require position input
* Input must be within grid bounds
* Invalid inputs are rejected with messages
* Flagged cells cannot be opened
* Timer continues during gameplay
* Input does not pause timer progression

---

## 8. 🎨 UX Design (Console)

* Clear grid display with row/column indices

### Symbols:

* Hidden → ■
* Flag → F
* Mine → *

### Game HUD:

* Time Left (seconds)
* Mines Remaining

Displayed above the board and updated every turn

---

## 9. 🏆 Win / Lose Conditions

### Win:

* All non-mine cells are opened

### Lose:

* Player opens a mine
* Timer reaches zero

---

## 9.1 🔁 Restart System

* After game ends, player is prompted:

  * Restart game
  * Exit game
* Game resets completely on restart

---

## 10. 🚀 Future Enhancements

* Color-coded numbers in console
* Pause / Resume functionality
* High score system (best time)
* Difficulty customization (custom grid & mines)
* First-click safe area (3×3 region)
* Save/Load game
* GUI version (Unity or Unreal Engine)
* Sound & animations

---

## 11. 🧠 Design Philosophy

This project focuses on:

* Clean architecture
* Logical problem-solving
* Separation of concerns
* Scalable design

---

## 12. 📌 Development Timeline (4 Days Plan)

| Day   | Task                        |
| ----- | --------------------------- |
| Day 1 | Board + Cell implementation |
| Day 2 | Mine logic + reveal system  |
| Day 3 | Input system + game loop    |
| Day 4 | Timer + polish + bug fixing |

---

## 13. 👨‍💻 Author

**Viresh Jadhav**

---

## 14. 📌 Summary

This Minesweeper clone demonstrates:

* Strong OOP fundamentals
* Recursive algorithms
* Game state management
* Countdown timer integration
* Console-based UI/UX design

---
