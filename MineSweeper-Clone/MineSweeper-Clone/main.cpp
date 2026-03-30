#include <iostream>
#include "Game/Board.h"
#include "UI/ConsoleUI.h"

using namespace N_Game;
using namespace N_UI;

int main()
{
    ConsoleUI ui;

    ui.showTitle();
    ui.showRule();
    ui.showHowToPlay();

    int difficulty = ui.getDifficultyChoice();

    Board board(static_cast<N_Game::Difficulty>(difficulty)); // assuming constructor handles setup

    int row, col;
    char action;

    while (true)
    {
        ui.showStartTitle();
        ui.displayBoard(board);

        ui.getUserInput(row, col, action, board);

        action = toupper(action);

        if (action == 'O')
        {
            board.openCell(row, col); // assuming implemented
        }
        else if (action == 'F')
        {
            board.flagToggle(row, col);
        }
        else
        {
            std::cout << "Invalid Input!" << std::endl;
        }
        
        ui.displayBoard(board);
        // temporary break condition for testing
        break;
    }

    return 0;
}