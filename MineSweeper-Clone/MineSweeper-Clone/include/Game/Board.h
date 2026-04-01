#pragma once

#include <iostream>
#include <vector>
#include <iomanip>
#include <random>
#include "Enums.h"
#include "Cell.h"

namespace N_Game
{
	class Board
	{
	private:
		// 2D grid of pointers to Cell objects (dynamic allocation)
		std::vector<std::vector<Cell*>> board;

		// Current game configuration
		Difficulty currentDifficulty;
		GameState currentGameState;

		// Random number generation for mine placement
		std::mt19937 randomEngine;
		std::random_device rd;
		
		// Board dimensions and mine count
		int numberOfRows;
		int numberOfColumns;
		int maxMines;

		// Tracks number of flagged cells by player
		int flaggedCells;

		// Ensures first click is always safe (no mine)
		bool firstCell;
		
		// Initializes board size and mine count based on difficulty
		void initializeBoard(Difficulty diff);

		// Allocates memory for board cells
		void createBoard();

		// Checks if given position is within board boundaries
		bool isValidPosition(int row, int col) const;

		// Randomly places mines on board (avoids first clicked cell)
		void placeMines(int row, int col);

		// Counts number of mines around a given cell
		int countMinesAround(int row, int col);

		// Assigns numbers (0–8) to non-mine cells
		void populateCells();

		// Recursively opens empty cells (flood fill logic)
		void processEmptyCell(int row, int col);

		// Reveals all mines when player loses
		void revealAllMines();

		// Checks if all non-mine cells are opened (win condition)
		bool checkAllCellOpen();

	public:
		// Constructor: initializes board with selected difficulty
		Board(Difficulty diff);

		// Destructor: releases allocated memory
		~Board();

		// Disable copy to prevent shallow copy issues (important for raw pointers)
		Board(const Board&) = delete;
		Board& operator=(const Board&) = delete;

		// Displays board in console
		void displayBoard();

		// Returns pointer to cell at given position (nullptr if invalid)
		Cell* getCell(int row, int col) const;

		// Handles opening a cell (main gameplay logic)
		void openCell(int row, int col);

		// Toggles flag on a cell
		void flagToggle(int row, int col);

		// Validates if a move is allowed
		bool isValidMove(int row, int col, char action) const;

		// Getters for board dimensions
		int getRows() const;
		int getColumns() const;

		// Frees all allocated cells and clears board
		void clearBoard();

		// Sets current game state (PLAYING, WON, LOST)
		void setGameState(GameState state);

		// Returns remaining mines (based on flags placed)
		int getRemainingMines() const;

		// Resets board for new game with given difficulty
		void reset(Difficulty diff);

		// Returns current game state
		GameState getGameState() const;

		// Returns true if game is over (win or loss)
		bool isGameOver() const;
	};
}