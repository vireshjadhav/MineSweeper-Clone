#pragma once

#include <iostream>
#include <vector>
#include <iomanip>
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
		
		int numberOfRows;
		int numberOfColumns;
		int minesCount;
		
		void initializeBoard(Difficulty diff);

		void createBoard();

		bool isValidPosition(int row, int col) const;



	public:
		Board(Difficulty diff);
		~Board();

		Board(const Board&) = delete;
		Board& operator=(const Board&) = delete;

		void displayBoard();

		Cell* getCell(int row, int col);
	};
}