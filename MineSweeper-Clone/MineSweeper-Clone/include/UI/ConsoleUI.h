#pragma once

#include <iostream>
#include "Utility/Utility.h"
#include "Game/Board.h"

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
		
		void showStartTitle();

		int getDifficultyChoice();
		
		void showInvalidCoordinates();
		
		void showInvalidAction();
		
		void getUserInput(int& row, int& col, char& action, N_Game::Board& board);
		
		void showGameOver();

		void displayBoard(N_Game::Board& board);
	};
}
