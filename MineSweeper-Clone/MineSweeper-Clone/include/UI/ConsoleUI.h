#pragma once

#include <iostream>
#include "Utility/Utility.h"
#include "Game/Board.h"
#include "Game/Timer.h"

namespace N_UI
{
	class ConsoleUI
	{
	private:
		N_Utility::Utility utility;

	public:
		ConsoleUI();

		~ConsoleUI();

		void showTitle();

		void showRule();
		
		void showHowToPlay();

		int getDifficultyChoice();
		
		void showInvalidCoordinates();
		
		void showInvalidAction();
		
		void getUserInput(int& row, int& col, char& action, N_Game::Board& board);

		void showGameStats(int remainingTime, int remainingMines);
		
		void showTimesUp();

		void showGameOver();

		void showGameWon();

		void displayBoard(N_Game::Board& board);
	};
}
