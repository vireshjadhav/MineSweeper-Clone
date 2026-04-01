#include <iomanip>
#include "UI/ConsoleUI.h"
#include "Utility/Utility.h"

using namespace N_Utility;
using namespace N_Game;
namespace N_UI
{
    ConsoleUI::ConsoleUI() {}

    ConsoleUI::~ConsoleUI() {}

    // Displays game title banner
	void ConsoleUI::showTitle()
	{
        std::cout << "                       ----------------------------------------------------------------------"
                   "\n                       |                                                                    |"
                   "\n                       |                  WELCOME TO MINESWEEPER GAME                       |"
                   "\n                       |                                                                    |"
                   "\n                       ----------------------------------------------------------------------" << std::endl;
	}

    // Displays game rules
    void ConsoleUI::showRule()
    {
        std::cout << "\n RULES: " << std::endl;
        std::cout << "1. The board is divided into cells, with mines randomly distributed." << std::endl;
        std::cout << "2. To win, you need to open all the cells." << std::endl;
        std::cout << "3. The number of a cell shows the number of mines adjacent to it. using this information, "
                     "\n   you can determine cells that are safe, and cells that contains mines." << std::endl;
        std::cout << "4. Interact, evolve and enjoy!";
        utility.waitForEnter(); // Pause for user to read
    }

    // Displays step-by-step instructions
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

    // Displays game over message (mine hit)
    void ConsoleUI::showGameOver()
    {
        std::cout << "\n                                         ************************************" << std::endl;
        std::cout << "                                         *            GAME OVER             *" << std::endl;
        std::cout << "                                         *      You stepped on a mine!      *" << std::endl;
        std::cout << "                                         ************************************" << std::endl;
    }

    // Displays game over message (time expired)
    void ConsoleUI::showTimesUp()
    {
        std::cout << "\n                                         ************************************" << std::endl;
        std::cout << "                                         *            GAME OVER             *" << std::endl;
        std::cout << "                                         *            Time's Up!            *" << std::endl;
        std::cout << "                                         ************************************" << std::endl;
    }

    // Displays win message
    void ConsoleUI::showGameWon()
    {
        std::cout << "\n                                         ************************************" << std::endl;
        std::cout << "                                         *             YOU WON!              *" << std::endl;
        std::cout << "                                         *     All safe cells uncovered!     *" << std::endl;
        std::cout << "                                         *************************************" << std::endl;
    }

    // Displays current game stats (time + mines left)
    void ConsoleUI::showGameStats(int remainingTime, int remainingMines)
    {
        std::cout << "\n                       ======================================================================="
                     "\n                       |                             MINESWEEPER                             |"
                     "\n                       |                         Time Left: " << std::setw(2) << std::setfill('0') << remainingTime << " sec                          |"
                     "\n                       |                           Mines Left: " << std::setw(2) << std::setfill('0') << remainingMines << "                            |"
                     "\n                       =======================================================================" << std::endl;
        std::cout << std::endl;
        std::cout << std::setfill(' ');         // Reset fill character
    }

    // Shows invalid coordinate message
    void ConsoleUI::showInvalidCoordinates()
    {
        std::cout << "Invalid coordinates. Try again." << std::endl;
    }

    // Shows invalid action message
    void ConsoleUI::showInvalidAction()
    {
        std::cout << "Invalid action. Use O or F or Q." << std::endl;
    }

    // Handles invalid input (cin fail state)
    void ConsoleUI::handleInputFailure()
    {
        utility.clearConsole();
        utility.clearInputBuffer();

        std::cout << "Invalid input format." << std::endl;
    }

    // Gets validated user input (loop until valid)
    void ConsoleUI::getUserInput(int& row, int& col, char& action, Board& board)
    {
        while (true)
        {
            std::cout << "Enter move (O Open/ F Flag/ Q Quit): ";
            std::cin >> action;

            action = toupper(action);       // Normalize input

            if (std::cin.fail())
            {
                handleInputFailure();
                continue;
            }

            // Quit option
            if (action == 'Q')
            {
                return;
            }

            // Validate action
            if (action != 'O' && action != 'F')
            {
                showInvalidAction();
                continue;
            }

            std::cout << "Enter Row and Column (e.g., 2 3): ";

            std::cin >> row >> col;

            if (std::cin.fail())
            {
                handleInputFailure();
                continue;
            }

            // Validate move with board logic
            if (!board.isValidMove(row, col, action))
            {
                showInvalidCoordinates();
                continue;
            }

            return;      // Valid input
        }
    }

    // Gets difficulty selection from user
    int ConsoleUI::getDifficultyChoice()
    {
        int diff;
        std::cout << "Please select a difficulty level: " << std::endl;
        std::cout << "1. Beginner  (9x9, 10 mines)" << std::endl;
        std::cout << "2. Intermediate (16x16, 40 mines)" << std::endl;
        std::cout << "3. Expert (21x21, 90 mines)" << std::endl;
        std::cout << "Register your input here: ";
        
        while (true)
        {
            std::cin >> diff;

            // Validate input
            if (std::cin.fail() || diff < 1 || diff > 3)
            {
                utility.clearInputBuffer();
                std::cout << "Invalid choice. Enter 1, 2, or 3:";
                continue;
            }
            break;
        }

        diff -= 1;      // Convert to 0-based enum

        utility.clearConsole();
        return diff;
    }

    // Displays board using Board class
    void ConsoleUI::displayBoard(Board& board)
    {
        board.displayBoard();
    }

    // Asks user to restart or quit
    bool ConsoleUI::confirmRestart()
    {
        char choice;
        std::cout << "Would you like to play again? (R = Restart, Q = Quit): ";
        while (true)
        {
            std::cin >> choice;

            choice = toupper(choice);

            if (choice == 'Q')
            {
                std::cout << "Exiting game...\n";
                return false;
            }
            else if (choice == 'R')
            {
                return true;
            }
            else
            {
                utility.clearInputBuffer();
                std::cout << "Invalid choice. Enter R = Restart or Q = Quit: ";
                continue;
            }
        }
    }
}