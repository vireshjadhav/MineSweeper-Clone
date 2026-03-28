# 🎮 Game Design Document (GDD)

## Project: Minesweeper (Console Edition)

---

## 1. 📌 Game Overview

**Genre:** Puzzle / Strategy
**Platform:** Console (C++)
**Target Audience:** Beginners to intermediate players who enjoy logical reasoning games

The game challenges players to clear a grid of hidden mines using logic and deduction.

---

## 2. 🎯 Objective

* Reveal all non-mine cells
* Avoid triggering any mine
* Use numerical clues to deduce safe cells

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

| Action      | Description               |
| ----------- | ------------------------- |
| Open Cell   | Reveals the selected cell |
| Flag Cell   | Marks suspected mine      |
| Unflag Cell | Removes flag              |

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

## 4. 🎮 Game Flow

1. Display rules and instructions
2. Player selects difficulty
3. Player enters first move
4. Board is generated (mines placed safely)
5. Loop:

   * Display board
   * Take input
   * Update board
   * Check win/lose condition
6. End game:

   * Win → All safe cells opened
   * Lose → Mine triggered

---

## 5. 🧠 Game States

* `PLAYING`
* `WON`
* `LOSE`

---

## 6. ⚙️ Technical Design

### 6.1 Core Classes

#### Cell

* Stores:

  * State (Hidden, Open, Flagged)
  * Type (Mine, Number, Empty)

#### Board

* Handles:

  * Grid creation
  * Mine placement
  * Neighbor calculations
  * Game rules

#### Gameplay

* Controls:

  * Game loop
  * State transitions

#### DisplayUI

* Handles:

  * User input
  * Output display

---

## 7. 🧪 Validation & Constraints

* Input must be within grid bounds
* Invalid inputs are rejected with messages
* Flagged cells cannot be opened

---

## 8. 🎨 UX Design (Console)

* Clear grid display with row/column indices
* Symbols:

  * Hidden → ■
  * Flag → ⚑
  * Mine → *
* Feedback messages for invalid actions

---

## 9. 🏆 Win / Lose Conditions

### Win:

* All non-mine cells are opened

### Lose:

* Player opens a mine

---

## 10. 🚀 Future Enhancements

* Timer system
* Difficulty customization
* Save/Load game
* GUI version (Unity or Unreal)
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
| Day 4 | Polish + bug fixing         |

---

## 13. 👨‍💻 Author

**Viresh Jadhav**

---

## 14. 📌 Summary

This Minesweeper clone demonstrates:

* Strong OOP fundamentals
* Recursive algorithms
* Game state management
* User interaction design

---
