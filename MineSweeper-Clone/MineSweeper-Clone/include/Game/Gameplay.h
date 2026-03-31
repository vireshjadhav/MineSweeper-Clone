#pragma once

#include "UI/ConsoleUI.h"
#include "Game/Board.h"
#include "Utility/Utility.h"

namespace N_Game
{
	class Gameplay
	{
	private:
		N_UI::ConsoleUI* ui;
		Board* board;
		N_Utility::Utility utility;

		void showRulesAndInstruction();

		void initializeGame();

		GameState getGameState() const; 

	public:
		Gameplay();
		~Gameplay();

		void run();
	};
}