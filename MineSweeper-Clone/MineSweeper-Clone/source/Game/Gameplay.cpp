#include "Game/Gameplay.h"
#include "Game/Board.h"
#include "UI/ConsoleUI.h"

using namespace N_UI;
namespace N_Game
{
	Gameplay::Gameplay() : timer(600)
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

		int second = 600;

		switch (diff)
		{
		case 2:
			second = 1200;
			break;

		case 1:
			second = 900;
			break;

		case 0:
			second = 600;
			break;
		}

		timer = Timer(second);

		board = new Board(static_cast<Difficulty>(diff));
		timer.reset();
		timer.start();
	}

	GameState Gameplay::getGameState() const
	{
		return board->getGameState();
	}

	void Gameplay::handleTimesUp()
	{
		utility.clearConsole();
		ui->showGameStats(timer.getRemainingSeconds(), board->getRemainingMines());
		board->displayBoard();
		ui->showTimesUp();
	}

	void Gameplay::run()
	{
		showRulesAndInstruction();
		initializeGame();

		utility.clearConsole();


		int row, col;
		char action;

		while (getGameState() == GameState::PLAYING)
		{

			if (timer.isTimeUp())
			{
				handleTimesUp();
				break;
			}

			utility.clearConsole();
			ui->showGameStats(timer.getRemainingSeconds(), board->getRemainingMines());
			
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

		if (timer.isTimeUp())
		{
			handleTimesUp();
		}
		else if (getGameState() == GameState::WON)
		{
			utility.clearConsole();
			ui->showGameStats(timer.getRemainingSeconds(), board->getRemainingMines());
			board->displayBoard();
			ui->showGameWon();
		}
		else if (getGameState() == GameState::LOST)
		{
			utility.clearConsole();
			ui->showGameStats(timer.getRemainingSeconds(), board->getRemainingMines());
			board->displayBoard();
			ui->showGameOver();
		}
	}
}