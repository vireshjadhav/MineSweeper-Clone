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
		// Utility helper for console operations (clear screen, input handling, etc.)
		N_Utility::Utility utility;

	public:
		// Constructor
		ConsoleUI();

		// Destructor
		~ConsoleUI();

		// Displays game title banner
		void showTitle();

		// Displays game rules
		void showRule();
		
		// Displays step-by-step instructions on how to play
		void showHowToPlay();

		// Prompts user to select difficulty level and returns choice (0–2)
		int getDifficultyChoice();
		
		// Displays error message for invalid board coordinates
		void showInvalidCoordinates();
		
		// Displays error message for invalid action input
		void showInvalidAction();
		
		// Gets validated user input (action, row, column)
		// Ensures input is valid before returning
		void getUserInput(int& row, int& col, char& action, N_Game::Board& board);

		// Displays game stats (remaining time and mines)
		void showGameStats(int remainingTime, int remainingMines);

		// Handles invalid input (cin failure), clears buffer and resets state
		void handleInputFailure();
		
		// Displays "Time's Up" game over message
		void showTimesUp();

		// Displays game over message (mine hit)
		void showGameOver();

		// Displays victory message
		void showGameWon();

		// Displays the current board state
		void displayBoard(N_Game::Board& board);

		// Asks user whether to restart or quit
		// Returns true = restart, false = quit
		bool confirmRestart();
	};
}
