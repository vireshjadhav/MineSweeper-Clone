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
		N_UI::ConsoleUI* ui;
		Board* board;
		N_Utility::Utility utility;
		Timer timer;

		void showRulesAndInstruction();

		void initializeGame();

		GameState getGameState() const; 

		void handleTimesUp();

	public:
		Gameplay();
		~Gameplay();

		void run();
	};
}