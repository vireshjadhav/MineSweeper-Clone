#pragma once

namespace N_Game
{
	// Defines difficulty levels for the game
	enum class Difficulty 
	{ 
		EASY, 
		MEDIUM, 
		HARD 
	};

	// Represents current game state
	enum class GameState 
	{ 
		PLAYING, 
		WON, 
		LOST 
	};

	// Represents visibility state of a cell
	enum class CellState 
	{ 
		HIDDEN, 
		OPEN, 
		FLAGGED 
	};
	
	// Represents type/content of a cell
	enum class CellType 
	{ 
		EMPTY, 
		ONE, 
		TWO, 
		THREE, 
		FOUR, 
		FIVE, 
		SIX, 
		SEVEN, 
		EIGHT, 
		MINE
	};
}
