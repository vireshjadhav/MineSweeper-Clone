#include <iostream>
#include "Game/Board.h"

using namespace N_Game;

int main()
{
    Board board(Difficulty::EASY);

    std::cout << "=== Initial Board ===\n";
    board.displayBoard();

    //    First move (safe click)
    std::cout << "\n=== First Move (Open 0,0) ===\n";
    board.openCell(0, 0);
    board.displayBoard();

    //    Try flagging some cells
    std::cout << "\n=== Flagging Cells ===\n";
    board.flagToggle(1, 1);
    board.flagToggle(2, 2);
    board.displayBoard();

    std::cout << "Remaining Mines: " << board.getRemainingMines() << "\n";

    //    Try unflag
    std::cout << "\n=== Unflag Cell (2,2) ===\n";
    board.flagToggle(2, 2);
    board.displayBoard();

    std::cout << "Remaining Mines: " << board.getRemainingMines() << "\n";

    //    Try opening flagged cell (should be blocked)
    std::cout << "\n=== Try Opening Flagged Cell (1,1) ===\n";
    board.openCell(1, 1);
    board.displayBoard();

    //    Open multiple cells to test flood fill
    std::cout << "\n=== Flood Fill Test ===\n";
    board.openCell(3, 3);
    board.displayBoard();

    //    Edge case: invalid input
    std::cout << "\n=== Invalid Input Test ===\n";
    board.openCell(-1, 100);  // should safely do nothing

    //    Try opening many cells (simulate gameplay)
    std::cout << "\n=== Gameplay Simulation ===\n";
    for (int r = 0; r < board.getRows(); r++)
    {
        for (int c = 0; c < board.getColumns(); c++)
        {
            board.openCell(r, c);
        }
    }

    board.displayBoard();

    std::cout << "\n=== Final State Reached ===\n";

    return 0;
}