#pragma once

#include "UI/ConsoleUI.h"
#include "Game/Board.h"
#include "Utility/Utility.h"
#include "Game/Timer.h"

namespace N_Game
{
	class Gameplay
	{
	private:
		// Console-based UI handler 
		N_UI::ConsoleUI ui;

		// Pointer to Board (dynamic allocation, must be deleted manually)
		Board* board;

		// Utility helper for console operations (clear screen, input handling, etc.)
		N_Utility::Utility utility;

		// Timer to track total gameplay time and countdown
		Timer timer;

		// Indicates whether the game ended due to time running out
		bool timeUp;

		// Displays rules and instructions at the start of the game
		void showRulesAndInstruction();

		// Initializes board, timer, and resets game state
		void initializeGame();

		// Retrieves current game state from Board
		GameState getGameState() const; 

		// Handles logic when time expires (forces game over)
		void handleTimesUp();

	public:
		// Constructor: initializes members and sets default state
		Gameplay();

		// Destructor: cleans up dynamically allocated Board
		~Gameplay();

		// Main game loop: controls input, updates, rendering, and timer checks
		void run();
	};
}