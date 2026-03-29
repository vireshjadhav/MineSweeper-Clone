#include "Game/Cell.h"

namespace N_Game
{
	// Default initialization: empty cell, hidden state
	Cell::Cell() :  currentCellType(CellType::EMPTY), currentCellState(CellState::OPEN) { }

	// Returns display string based on current cell state
	std::string Cell::getCellString() const
	{
		switch (currentCellState)
		{
		case CellState::HIDDEN:
			return "\xDB";                         // Block character representing hidden cell
		case CellState::FLAGGED:
			return "F";                            // Flag marker
		case CellState::OPEN:
			return getCellStringWhenOpened();      // Delegate to type-based rendering
		default:
			return "\xDB";						   // Fallback safety
		}
	}

	// Returns display string when cell is opened (based on type)
	std::string Cell::getCellStringWhenOpened() const
	{
		switch (currentCellType)
		{
		case CellType::EMPTY:
			return " ";
		case CellType::ONE:
			return "1";
		case CellType::TWO:
			return "2";
		case CellType::THREE:
			return "3";
		case CellType::FOUR:
			return "4";
		case CellType::FIVE:
			return "5";
		case CellType::SIX:
			return "6";
		case CellType::SEVEN:
			return "7";
		case CellType::EIGHT:
			return "8";
		case CellType::MINE:
			return "*";
		default:
			return " ";			// Fallback safety
		}
	}

	CellType Cell::getCellType() const
	{
		return currentCellType;
	}

	void Cell::setCellType(CellType type) 
	{
		currentCellType = type;
	}

	CellState Cell::getCellState() const
	{
		return currentCellState;
	}

	void Cell::setCellState(CellState state)
	{
		currentCellState = state;
	}

	// Public interface for rendering the cell
	std::string Cell::getCellDisplayString() const
	{
		return getCellString();
	}
}