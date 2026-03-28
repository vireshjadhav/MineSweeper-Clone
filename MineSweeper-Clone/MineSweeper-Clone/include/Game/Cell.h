#pragma once

#include <string>
#include "../Game/Enums.h"

namespace N_Game
{
	// Represents a single cell in the Minesweeper grid.
	// Stores cell type (mine/number) and state (hidden/open/flagged),
	// and provides display output based on current state.
	class Cell
	{
	private:
		CellType currentCellType;                        // Type of cell (EMPTY, ONE...MINE)
		CellState currentCellState;						 // Current state (HIDDEN, OPEN, FLAGGED)

		// Computes display string based on current state
		std::string getCellString() const;

		// Computes display string when the cell is opened
		std::string getCellStringWhenOpened() const;

	public:
		// Initializes cell as EMPTY and HIDDEN
		Cell();      

		// Returns the string representation used for rendering the cell
		std::string getCellDisplayString() const;

		/* Getters and setters for cell type and state */ 
		CellType getCellType() const;
		void setCellType(CellType type);

		CellState getCellState() const;
		void setCellState(CellState state);
	};
}