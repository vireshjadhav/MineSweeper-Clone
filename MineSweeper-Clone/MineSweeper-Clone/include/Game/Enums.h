#pragma once

namespace N_Game
{
	enum class Difficulty { EASY, MEDIUM, HARD };
	enum class GameState { PLAYING, WON, LOST };
	enum class CellState { HIDDEN, OPEN, FLAGGED };
	enum class CellType { EMPTY, ONE, TWO, THREE, FOUR, FIVE, SIX, SEVEN, EIGHT, MINE};
}
