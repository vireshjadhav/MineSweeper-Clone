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
		std::vector<std::vector<Cell*>> board;

		Difficulty currentDifficulty;
		GameState currentGameState;

		std::mt19937 randomEngine;
		std::random_device rd;
		
		int numberOfRows;
		int numberOfColumns;
		int maxMines;
		int flaggedCells;

		bool firstCell;
		
		void initializeBoard(Difficulty diff);

		void createBoard();

		bool isValidPosition(int row, int col) const;


		void placeMines(int row, int col);

		int countMinesAround(int row, int col);

		void populateCells();

		void processEmptyCell(int row, int col);

		void revealAllMines();

		bool checkAllCellOpen();

		void clearBoard();

	public:
		Board(Difficulty diff);
		~Board();

		Board(const Board&) = delete;
		Board& operator=(const Board&) = delete;

		void displayBoard();

		Cell* getCell(int row, int col) const;

		void openCell(int row, int col);

		void flagToggle(int row, int col);

		bool isValidMove(int row, int col, char action) const;

		int getRows();

		int getColumns();

		void setGameState(GameState state);

		int getRemainingMines();

		void reset(Difficulty diff);

		GameState getGameState() const;

		bool isGameOver() const;
	};
}