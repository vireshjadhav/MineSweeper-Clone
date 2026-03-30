#include "Game/Board.h"

namespace N_Game
{
	Board::Board(Difficulty diff)
	{
		firstCell = true;
		flaggedCells = 0;
		currentDifficulty = diff;
		currentGameState = GameState::PLAYING;

		randomEngine.seed(rd());

		initializeBoard(currentDifficulty);
	}

	Board::~Board() 
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

		default:
			numberOfRows = 9;
			numberOfColumns = 9;
			maxMines = 10;
			break;
		}
		createBoard();
	}

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

	void Board::displayBoard()
	{
		std::string padding;
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

		std::cout << padding << "   ";
		for (size_t i = 0; i < numberOfColumns; ++i)
		{
			std::cout << std::setw(3) << i << " ";
		}
		std::cout << std::endl;

		std::cout << padding << "   ";
		for (size_t col = 0; col < numberOfColumns; ++col)
		{
			std::cout << "----";
		}
		std::cout << "-" << std::endl;

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

			if ((rowFirst == row && colFirst == col) || cell->getCellType() == CellType::MINE)
			{
				continue;
			}

			if (cell && cell->getCellType() != CellType::MINE)
			{
				cell->setCellType(CellType::MINE);
				++minesPlaced;
			}
		}
	}

	int Board::countMinesAround(int row, int col)
	{
		int minesAround = 0;

		for (int a = -1; a <= 1; ++a)
		{
			for (int b = -1; b <= 1; ++b)
			{
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
					cell->setCellType(static_cast<CellType>(minesAround));
				}
			}
		}
	}

	Cell* Board::getCell(int row, int col) const
	{
		if (!isValidPosition(row, col))
			return nullptr;
		return board[row][col];
	}

	bool Board::isValidPosition(int row, int col) const
	{
		return (row >= 0 && col >= 0 && row < numberOfRows && col < numberOfColumns);
	}

	void Board::openCell(int row, int col)
	{
		if (currentGameState != GameState::PLAYING)
		{
			return;
		}

		Cell* cell = getCell(row, col);

		if (!cell) return;

		if (firstCell)
		{
			placeMines(row, col);
			populateCells();
			firstCell = false;
		}

		if (cell->getCellState() == CellState::FLAGGED)
		{
			std::cout << "Cell (" << row << ", " << col << ") is flagged. "
				<< "Use 'F' again to unflag it first." << std::endl;
			return;
		}

		if (cell->getCellState() == CellState::OPEN)
		{
			return;
		}

		switch (cell->getCellType())
		{
		case CellType::EMPTY:
			processEmptyCell(row, col);
			break;

		case CellType::MINE:
			revealAllMines();
			currentGameState = GameState::LOST;
			return;

		default:
			cell->setCellState(CellState::OPEN);
			break;
		}

		if (checkAllCellOpen())
		{
			setGameState(GameState::WON);
		}
	}

	void Board::processEmptyCell(int row, int col)
	{
		Cell* cell = getCell(row, col);

		if (cell->getCellState() == CellState::OPEN || cell->getCellState() == CellState::FLAGGED)
		{
			return;
		}

		cell->setCellState(CellState::OPEN);

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

					if (neighborCell->getCellState() == CellState::FLAGGED)
					{
						continue;
					}

					if (neighborCell->getCellType() != CellType::MINE)
					{
						processEmptyCell(neighborRow, neighborCol);
					}
				}
			}
		}
	}

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

	void Board::flagToggle(int row, int col)
	{
		if (currentGameState != GameState::PLAYING)
		{
			return;
		}

		Cell* cell = getCell(row, col);

		if (!cell) return;

		if (cell->getCellState() == CellState::OPEN)
		{
			return;
		}

		if (cell->getCellState() == CellState::FLAGGED)
		{
			cell->setCellState(CellState::HIDDEN);
			flaggedCells--;
		}
		else
		{
			cell->setCellState(CellState::FLAGGED);
			flaggedCells++;
		}
	}

	void Board::setGameState(GameState state)
	{
		currentGameState = state;
	}

	int Board::getRows() { return numberOfRows;	}

	int Board::getColumns() { return numberOfColumns; }

	int Board::getRemainingMines() { return maxMines - flaggedCells; }

	void Board::clearBoard()
	{
		for (int row = 0; row < numberOfRows; ++row)
		{
			for (int col = 0; col < numberOfColumns; ++col)
			{
				delete board[row][col];
			}
		}
		board.clear();
	}

	void Board::reset(Difficulty diff)
	{
		clearBoard();

		firstCell = true;
		flaggedCells = 0;
		currentGameState = GameState::PLAYING;

		initializeBoard(diff);
	}

	bool Board::isValidMove(int row, int col, char action)  const
	{
		if (row < 0 || row >= numberOfRows || col < 0 || col >= numberOfColumns)
			return false;

		Cell* cell = getCell(row, col);

		if (action == 'O' && cell->getCellState() == CellState::OPEN)
			return false;
		
		if (action == 'F' && cell->getCellState() == CellState::OPEN)
			return false;

		return true;
	}

	GameState Board::getGameState() const { return currentGameState; }

	bool Board::isGameOver() const { return currentGameState != GameState::PLAYING; }
}