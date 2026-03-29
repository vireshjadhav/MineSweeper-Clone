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
		
		void initializeBoard(Difficulty diff);

		void createBoard();

		bool isValidPosition(int row, int col) const;

		void placeMines();

		int countMinesAround(int row, int col);

		void populateCells();

	public:
		Board(Difficulty diff);
		~Board();

		Board(const Board&) = delete;
		Board& operator=(const Board&) = delete;

		void displayBoard();

		Cell* getCell(int row, int col);
	};
}