#include "Game/Gameplay.h"
#include "Game/Board.h"
#include "UI/ConsoleUI.h"

using namespace N_UI;
namespace N_Game
{
	// Constructor: initializes timer with default value and board pointer
	Gameplay::Gameplay() : timer(600)
	{
		board = nullptr;		// Important: avoid dangling pointer
	}

	// Destructor: free dynamically allocated board
	Gameplay::~Gameplay()
	{
		delete(board);			// Safe even if nullptr
	}

	// Displays title, rules, and instructions
	void Gameplay::showRulesAndInstruction()
	{
		ui.showTitle();
		ui.showRule();
		ui.showHowToPlay();
	}

	// Initializes game state based on user difficulty selection
	void Gameplay::initializeGame()
	{
		int diff = ui.getDifficultyChoice();

		// Delete previous board to avoid memory leak
		if (board)
		{
			delete board;
		}

		// Default time (in seconds)
		int second = 600;

		// Set timer based on difficulty
		switch (diff)
		{
		case 2: second = 1200; break;	// HARD
		case 1: second = 900; break;	// MEDIUM
		case 0: second = 600; break;	// EASY
		}

		// Reinitialize timer with new duration
		timer = Timer(second);

		// Create new board based on difficulty
		board = new Board(static_cast<Difficulty>(diff));
		timer.reset();
		timer.start();

		timeUp = false;
	}

	// Returns current game state from board
	GameState Gameplay::getGameState() const
	{
		return board->getGameState();
	}

	// Handles scenario when time runs out
	void Gameplay::handleTimesUp()
	{
		utility.clearConsole();

		// Show final stats and full board
		ui.showGameStats(timer.getRemainingSeconds(), board->getRemainingMines());
		board->displayBoard();

		ui.showTimesUp();
	}

	// Main game loop
	void Gameplay::run()
	{
		while (true)			// Game restart loop
		{
			showRulesAndInstruction();
			initializeGame();

			utility.clearConsole();


			int row, col;
			char action;

			// Main gameplay loop
			while (getGameState() == GameState::PLAYING)
			{
				// Check if time has expired
				if (timer.isTimeUp())
				{
					timeUp = true;
					break;
				}

				utility.clearConsole();

				// Show timer + remaining mines
				ui.showGameStats(timer.getRemainingSeconds(), board->getRemainingMines());

				// Display current board state
				ui.displayBoard(*board);

				// Timer does NOT update while waiting for input
				ui.getUserInput(row, col, action, *board);

				// Handle user action
				switch (action)
				{
				case 'O':
					board->openCell(row, col);
					break;

				case 'F':
					board->flagToggle(row, col);
					break;

				case 'Q':
					return;					// Exit game completely

				default:
					std::cout << "Invalid user input!";
					break;
				}
			}

			// Handle end-of-game scenarios
			if (timeUp)
			{
				handleTimesUp();
			}
			else if (getGameState() == GameState::WON)
			{
				utility.clearConsole();
				ui.showGameStats(timer.getRemainingSeconds(), board->getRemainingMines());
				board->displayBoard();
				ui.showGameWon();
			}
			else if (getGameState() == GameState::LOST)
			{
				utility.clearConsole();
				ui.showGameStats(timer.getRemainingSeconds(), board->getRemainingMines());
				board->displayBoard();
				ui.showGameOver();
			}

			// Ask player if they want to restart
			if (!ui.confirmRestart())
			{
				return;						// Exit game loop
			}
		}
	}
}