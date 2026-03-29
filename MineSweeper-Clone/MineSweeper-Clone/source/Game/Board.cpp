#include "Game/Board.h"

namespace N_Game
{
	Board::Board(Difficulty diff)
	{
		currentDifficulty = diff;
		currentGameState = GameState::PLAYING;
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
			minesCount = 10;
			break;

		case Difficulty::MEDIUM:
			numberOfRows = 16;
			numberOfColumns = 16;
			minesCount = 40;
			break;

		case Difficulty::HARD:
			numberOfRows = 21;
			numberOfColumns = 21;
			minesCount = 90;
			break;

		default:
			numberOfRows = 9;
			numberOfColumns = 9;
			minesCount = 10;
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