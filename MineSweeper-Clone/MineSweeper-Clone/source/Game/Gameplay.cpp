#include "Game/Gameplay.h"
#include "Game/Board.h"
#include "UI/ConsoleUI.h"

using namespace N_UI;
namespace N_Game
{
	Gameplay::Gameplay()
	{
		ui = new ConsoleUI();
		board = nullptr;
	}

	Gameplay::~Gameplay()
	{
		delete(ui);
		delete(board);
	}

	void Gameplay::showRulesAndInstruction()
	{
		ui->showTitle();
		ui->showRule();
		ui->showHowToPlay();
	}

	void Gameplay::initializeGame()
	{
		int diff = ui->getDifficultyChoice();

		if (board)
		{
			delete board;
		}

		board = new Board(static_cast<Difficulty>(diff));
	}

	GameState Gameplay::getGameState() const
	{
		return board->getGameState();
	}

	void Gameplay::run()
	{
		showRulesAndInstruction();
		initializeGame();

		utility.clearConsole();

		ui->showStartTitle();

		int row, col;
		char action;

		while (getGameState() == GameState::PLAYING)
		{
			ui->displayBoard(*board);

			ui->getUserInput(row, col, action, *board);

			switch (action)
			{
			case 'O':
				board->openCell(row, col);
				break;

			case 'F':
				board->flagToggle(row, col);
				break;

			default:
				std::cout << "Invalid user input!";
				break;
			}
		}

		if (getGameState() == GameState::WON)
		{
			board->displayBoard();
			ui->showGameWon();
		}
		else if (getGameState() == GameState::LOST)
		{
			board->displayBoard();
			ui->showGameOver();
		}
	}
}