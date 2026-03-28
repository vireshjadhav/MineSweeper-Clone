🎮 Minesweeper (Console Version)
📌 Overview

This project is a console-based implementation of the classic Minesweeper game, developed using C++ and Object-Oriented Programming (OOP) principles.

The game allows players to uncover cells, flag potential mines, and strategically clear the board without triggering a mine.

🚀 Features
Multiple difficulty levels:
    •Beginner (9×9, 10 mines)
    •Intermediate (16×16, 40 mines)
    •Expert (21×21, 90 mines)
First-click safety (first move never hits a mine)
Recursive cell reveal (auto-expansion of empty cells)
Flag and unflag system
Input validation for safe gameplay
Dynamic board display after every move
Win/Lose detection

🎮 How to Play
Controls
O row col → Open a cell
F row col → Flag a cell
U row col → Unflag a cell
Example
O 3 4
F 2 5

📜 Game Rules
The board contains hidden mines.
Opening a mine results in game over.
Numbers indicate how many mines are adjacent to that cell.
Open all non-mine cells to win the game.

🧠 Game Logic Highlights
First Click Safety
Mines are generated after the first move
Ensures the first clicked cell is always safe
Recursive Reveal
Empty cells automatically reveal neighboring cells
Stops at numbered cells

🏗️ Project Structure
N_Utility   → Helper functions (console, input handling)
N_Display   → UI and user interaction
N_Game      → Core game logic
    ├── Cell
    ├── Board
    └── Gameplay

🧩 OOP Concepts Used
Encapsulation (Cell, Board classes)
Abstraction (Game logic hidden behind methods)
Modular design (separate namespaces)
Dynamic memory management

⚙️ How to Run
Compile:
g++ main.cpp -o minesweeper
Run:
./minesweeper

✨ Future Improvements
Timer system ⏱
High score tracking 🏆
Keyboard navigation (WASD)
GUI version using Unity 🎮
Sound effects 🔊


👨‍💻 Author

Viresh Jadhav

📌 Notes

This project was built as part of a structured assignment to improve:

Problem-solving skills
OOP design thinking
Game logic implementation

⭐ If you like this project, consider giving it a star!