#include "Game/Board.h"

namespace N_Game
{
	// Constructor: Initializes board state and seeds random engine
	Board::Board(Difficulty diff)
	{
		firstCell = true;                                  // First click safety flag
		flaggedCells = 0;								   // Track number of flagged cells
		currentDifficulty = diff;                          // Store selected difficulty
		currentGameState = GameState::PLAYING;             // Initial game state

		randomEngine.seed(rd());                           // Seed RNG with random device

		initializeBoard(currentDifficulty);                // Setup board dimensions and cells
	}

	// Destructor: Clean up dynamically allocated memory
	Board::~Board() 
	{
		clearBoard();
	}

	// Sets board size and mine count based on difficulty
	void Board::initializeBoard(Difficulty diff)
	{
		switch (diff)
		{
		case Difficulty::EASY:
			numberOfRows = 9;
			numberOfColumns = 9;
			maxMines = 10;
			break;

		case Difficulty::MEDIUM:
			numberOfRows = 16;
			numberOfColumns = 16;
			maxMines = 40;
			break;

		case Difficulty::HARD:
			numberOfRows = 21;
			numberOfColumns = 21;
			maxMines = 90;
			break;

		default:						    // Fallback safety
			numberOfRows = 9;
			numberOfColumns = 9;
			maxMines = 10;
			break;
		}
		createBoard();					    // Allocate cells
	}

	// Allocates 2D grid of Cell pointers
	void Board::createBoard()
	{
		board.resize(numberOfRows);
		for (int row = 0; row < numberOfRows; ++row)
		{
			board[row].resize(numberOfColumns);
			for (int col = 0; col < numberOfColumns; ++col)
			{
				board[row][col] = new Cell();
			}
		}
	}

	// Displays board in console with formatting
	void Board::displayBoard()
	{
		std::string padding;

		// Adjust UI spacing based on board size
		switch (currentDifficulty)
		{
		case Difficulty::EASY:
			padding = "                                      ";
			break;
		case Difficulty::MEDIUM:
			padding = "                        ";
			break;
		case Difficulty::HARD:
			padding = "              ";
			break;
		}

		// Column headers
		std::cout << padding << "   ";
		for (size_t i = 0; i < numberOfColumns; ++i)
		{
			std::cout << std::setw(3) << i << " ";
		}
		std::cout << std::endl;

		// Top border
		std::cout << padding << "   ";
		for (size_t col = 0; col < numberOfColumns; ++col)
		{
			std::cout << "----";
		}
		std::cout << "-" << std::endl;

		// Rows
		for (size_t row = 0; row < numberOfRows; ++row)
		{
			std::cout << padding << std::setw(2) << row << " ";

			for (size_t col = 0; col < numberOfColumns; ++col)
			{
				std::cout << "|" << std::setw(2) << board[row][col]->getCellDisplayString() << " ";
			}
			std::cout << "|" << std::endl;

			std::cout << padding <<  "   ";

			for (size_t col = 0; col < numberOfColumns; ++col)
			{
				std::cout << "----";
			}
			std::cout << "-" << std::endl;
		}
	}

	// Randomly places mines, avoiding first clicked cell
	void Board::placeMines(int rowFirst, int colFirst)
	{
		std::uniform_int_distribution<int> rowDist(0, numberOfRows - 1);
		std::uniform_int_distribution<int> colDist(0, numberOfColumns - 1);

		int minesPlaced = 0;
		while (minesPlaced < maxMines)
		{
			int row = rowDist(randomEngine);
			int col = colDist(randomEngine);

			Cell* cell = getCell(row, col);

			// Skip first clicked cell and already placed mines
			if ((rowFirst == row && colFirst == col) || cell->getCellType() == CellType::MINE)
			{
				continue;
			}

			// Place mine
			if (cell && cell->getCellType() != CellType::MINE)
			{
				cell->setCellType(CellType::MINE);
				++minesPlaced;
			}
		}
	}

	// Counts number of mines around a given cell
	int Board::countMinesAround(int row, int col)
	{
		int minesAround = 0;

		for (int a = -1; a <= 1; ++a)
		{
			for (int b = -1; b <= 1; ++b)
			{
				// Skip self and invalid positions
				if ((a == 0 && b == 0) || !isValidPosition(row + a, col + b))
				{
					continue;
				}

				if (getCell(row + a, col + b)->getCellType() == CellType::MINE)
				{
					minesAround++;
				}
			}
		}

		return minesAround;
	}

	// Assigns numbers to non-mine cells
	void Board::populateCells()
	{
		for (int row = 0; row < numberOfRows; ++row)
		{
			for (int col = 0; col < numberOfColumns; ++col)
			{
				Cell* cell = getCell(row, col);
				if (cell && cell->getCellType() != CellType::MINE)
				{
					int minesAround = countMinesAround(row, col);

					// Store number as CellType (0–8)
					cell->setCellType(static_cast<CellType>(minesAround));
				}
			}
		}
	}

	// Returns pointer to cell, or nullptr if invalid
	Cell* Board::getCell(int row, int col) const
	{
		if (!isValidPosition(row, col))
			return nullptr;
		return board[row][col];
	}

	// Checks if given position is inside board bounds
	bool Board::isValidPosition(int row, int col) const
	{
		return (row >= 0 && col >= 0 && row < numberOfRows && col < numberOfColumns);
	}

	// Handles opening a cell
	void Board::openCell(int row, int col)
	{
		// Ignore if game already ended
		if (currentGameState != GameState::PLAYING)
		{
			return;
		}

		Cell* cell = getCell(row, col);

		if (!cell) return;

		// First click: generate mines AFTER first move
		if (firstCell)
		{
			placeMines(row, col);
			populateCells();
			firstCell = false;
		}

		// Prevent opening flagged cells
		if (cell->getCellState() == CellState::FLAGGED)
		{
			std::cout << "Cell (" << row << ", " << col << ") is flagged. "
				<< "Use 'F' again to unflag it first." << std::endl;
			return;
		}

		// Ignore already opened cells
		if (cell->getCellState() == CellState::OPEN)
		{
			return;
		}

		// Handle based on cell type
		switch (cell->getCellType())
		{
		case CellType::EMPTY:
			processEmptyCell(row, col);				// Flood fill
			break;

		case CellType::MINE:
			revealAllMines();
			currentGameState = GameState::LOST;
			return;

		default:
			cell->setCellState(CellState::OPEN);
			break;
		}

		// Check win condition
		if (checkAllCellOpen())
		{
			setGameState(GameState::WON);
		}
	}

	// Recursive flood fill for empty cells
	void Board::processEmptyCell(int row, int col)
	{
		Cell* cell = getCell(row, col);

		// Stop if already processed or flagged
		if (cell->getCellState() == CellState::OPEN || cell->getCellState() == CellState::FLAGGED)
		{
			return;
		}

		cell->setCellState(CellState::OPEN);

		// Expand only if empty
		if (cell->getCellType() == CellType::EMPTY)
		{
			for (int a = -1; a <= 1; ++a)
			{
				for (int b = -1; b <= 1; ++b)
				{
					int neighborRow = row + a;
					int neighborCol = col + b;

					if ((a == 0 && b == 0) || !isValidPosition(neighborRow, neighborCol))
					{
						continue;
					}

					Cell* neighborCell = getCell(neighborRow, neighborCol);

					// Skip flagged cells
					if (neighborCell->getCellState() == CellState::FLAGGED)
					{
						continue;
					}

					// Recurse if safe
					if (neighborCell->getCellType() != CellType::MINE)
					{
						processEmptyCell(neighborRow, neighborCol);
					}
				}
			}
		}
	}

	// Reveals all mines (game over)
	void Board::revealAllMines()
	{
		for (int row = 0; row < numberOfRows; ++row)
		{
			for (int col = 0; col < numberOfColumns; ++col)
			{
				Cell* cell = getCell(row, col);
				if (cell->getCellType() == CellType::MINE)
				{
					cell->setCellState(CellState::OPEN);
				}
			}
		}
	}

	// Checks if all safe cells are opened (win condition)
	bool Board::checkAllCellOpen()
	{
		int totalCell = numberOfRows * numberOfColumns;
		int cellCount = 0;

		for (int row = 0; row < numberOfRows; ++row)
		{
			for (int col = 0; col < numberOfColumns; ++col)
			{
				Cell* cell = getCell(row, col);

				if(cell->getCellState() == CellState::OPEN && cell->getCellType() != CellType::MINE)
				{
					cellCount++;
				}
			}
		}

		return cellCount == totalCell - maxMines;
	}

	// Toggles flag state on a cell
	void Board::flagToggle(int row, int col)
	{
		if (currentGameState != GameState::PLAYING)
		{
			return;
		}

		Cell* cell = getCell(row, col);
		if (!cell) return;

		// Cannot flag opened cell
		if (cell->getCellState() == CellState::OPEN)
		{
			return;
		}

		if (cell->getCellState() == CellState::FLAGGED)
		{
			cell->setCellState(CellState::HIDDEN);
			flaggedCells = std::max(0, flaggedCells - 1);
		}
		else
		{
			cell->setCellState(CellState::FLAGGED);
			flaggedCells = std::min(maxMines, flaggedCells + 1);
		}
	}

	// Sets current game state
	void Board::setGameState(GameState state)
	{
		currentGameState = state;
	}

	// Getters
	int Board::getRows() const { return numberOfRows;	}

	int Board::getColumns() const { return numberOfColumns; }

	int Board::getRemainingMines() const { return maxMines - flaggedCells; }

	GameState Board::getGameState() const { return currentGameState; }

	// Returns true if game is finished
	bool Board::isGameOver() const { return currentGameState != GameState::PLAYING; }

	// Frees all dynamically allocated cells
	void Board::clearBoard()
	{
		if (!board.empty())
		{
			for (int row = 0; row < numberOfRows; ++row)
			{
				for (int col = 0; col < numberOfColumns; ++col)
				{
					delete board[row][col];
					board[row][col] = nullptr;
				}
			}
		}
		board.clear();
	}

	// Resets board for new game
	void Board::reset(Difficulty diff)
	{
		clearBoard();

		firstCell = true;
		flaggedCells = 0;
		currentGameState = GameState::PLAYING;

		initializeBoard(diff);
	}

	// Validates user move
	bool Board::isValidMove(int row, int col, char action)  const
	{
		if (row < 0 || row >= numberOfRows || col < 0 || col >= numberOfColumns)
			return false;

		Cell* cell = getCell(row, col);

		// Cannot open or flag already opened cell
		if (action == 'O' && cell->getCellState() == CellState::OPEN)
			return false;
		
		if (action == 'F' && cell->getCellState() == CellState::OPEN)
			return false;

		return true;
	}
}