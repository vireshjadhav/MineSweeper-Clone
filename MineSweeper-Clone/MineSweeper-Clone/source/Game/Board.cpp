#include "Game/Board.h"

namespace N_Game
{
	Board::Board(Difficulty diff)
	{
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

		placeMines();
		populateCells();
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

	void Board::placeMines()
	{
		std::uniform_int_distribution<int> rowDist(0, numberOfRows - 1);
		std::uniform_int_distribution<int> colDist(0, numberOfColumns - 1);

		int minesPlaced = 0;
		while (minesPlaced < maxMines)
		{
			int row = rowDist(randomEngine);
			int col = colDist(randomEngine);

			Cell* cell = getCell(row, col);

			if (cell && cell->getCellType() != CellType::MINE)
			{
				cell->setCellType(CellType::MINE);
				++minesPlaced;
			}
		}

		std::cout << "Mines Placed: " << minesPlaced << std::endl;  //debug message
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

	Cell* Board::getCell(int row, int col)
	{
		if (!isValidPosition(row, col))
			return nullptr;
		return board[row][col];
	}

	bool Board::isValidPosition(int row, int col) const
	{
		return (row >= 0 && col >= 0 && row < numberOfRows && col < numberOfColumns);
	}
}