#include "UI/ConsoleUI.h"
#include "Utility/Utility.h"

using namespace N_Utility;
using namespace N_Game;
namespace N_UI
{
    ConsoleUI::ConsoleUI() {}

    ConsoleUI::~ConsoleUI() {}

	void ConsoleUI::showTitle()
	{
        std::cout << "----------------------------------------------------------------------"
                   "\n|                                                                    |"
                   "\n|                  WELCOME TO MINESWEEPER GAME                       |"
                   "\n|                                                                    |"
                   "\n----------------------------------------------------------------------" << std::endl;
	}

    void ConsoleUI::showRule()
    {
        std::cout << "\n RULES: " << std::endl;
        std::cout << "1. The board is divided into cells, with mines randomly distributed." << std::endl;
        std::cout << "2. To win, you need to open all the cells." << std::endl;
        std::cout << "3. The number of a cell shows the number of mines adjacent to it. using this information, "
                     "\n   you can determine cells that are safe, and cells that contains mines." << std::endl;
        std::cout << "4. Interact, evolve and enjoy!";
        utility.waitForEnter();
    }

    void ConsoleUI::showStartTitle()
    {
        std::cout << "\n                       -----------------------------------------------------------------------"
                     "\n                       |                                                                     |"
                     "\n                       |                            GAME STARTS                              |"
                     "\n                       |                                                                     |"
                     "\n                       -----------------------------------------------------------------------" << std::endl;
    }

    void ConsoleUI::showHowToPlay()
    {
        std::cout << "\n======How to Play======\n" << std::endl;

        std::cout << "1. Enter your move in the format:" << std::endl;
        std::cout << "   <Action> <Row> <Column>" << std::endl;
        std::cout << "   Example: O 2 3" << std::endl;

        utility.waitForEnter();

        std::cout << "2. Actions:" << std::endl;
        std::cout << "   O - Open a cell" << std::endl;
        std::cout << "   F - Flag or unflag a cell" << std::endl;

        utility.waitForEnter();

        std::cout << "3. Row and Column indices start from 0." << std::endl;
        std::cout << "   Example: (0, 0) is the top-left cell." << std::endl;

        utility.waitForEnter();

        std::cout << "4. Opening a cell:" << std::endl;
        std::cout << "   - If it contains a mine, the game ends." << std::endl;
        std::cout << "   - Otherwise, it shows the number of adjacent mines." << std::endl;

        utility.waitForEnter();

        std::cout << "5. Flagging a cell:" << std::endl;
        std::cout << "   - Use flags to mark suspected mines." << std::endl;

        utility.waitForEnter();
    }

    void ConsoleUI::showGameOver()
    {
        std::cout << "**BOOM! You step on Mine!**" << std::endl;
        std::cout << "***Game Over***" << std::endl;
    }

    void ConsoleUI::showInvalidCoordinates()
    {
        std::cout << "Invalid coordinates. Try again." << std::endl;
    }

    void ConsoleUI::showInvalidAction()
    {
        std::cout << "Invalid action. Use O or F." << std::endl;
    }

    void ConsoleUI::getUserInput(int& row, int& col, char& action, Board& board)
    {
        while (true)
        {
            std::cout << "Enter move (O Open/ F Flag) followed by Row and Col: ";

            std::cin >> action >> row >> col;

            action = toupper(action);

            if (std::cin.fail())
            {
                utility.clearConsole();
                utility.clearInputBuffer();

                std::cout << "Invalid input format." << std::endl;
                continue;
            }

            if (action != 'O' && action != 'F')
            {
                showInvalidAction();
                continue;
            }

            if (!board.isValidMove(row, col, action))
            {
                showInvalidCoordinates();
                continue;
            }

            return;
        }
    }

    int ConsoleUI::getDifficultyChoice()
    {
        utility.clearInputBuffer();
        int diff;
        std::cout << "Please select a difficulty level: " << std::endl;
        std::cout << "1. Beginner  (9x9, 10 mines)" << std::endl;
        std::cout << "2. Intermediate (16x16, 40 mines)" << std::endl;
        std::cout << "3. Expert (21x21, 90 mines)" << std::endl;
        std::cout << "Register your input here: ";
        
        while (true)
        {
            std::cin >> diff;

            if (std::cin.fail() || diff < 1 || diff > 3)
            {
                utility.clearInputBuffer();
                std::cout << "Invalid choice. Enter 1, 2, or 3:";
                continue;
            }
            break;
        }

        diff -= 1;

        return diff;
        utility.clearConsole();
    }

    void ConsoleUI::displayBoard(Board& board)
    {
        board.displayBoard();
    }
}