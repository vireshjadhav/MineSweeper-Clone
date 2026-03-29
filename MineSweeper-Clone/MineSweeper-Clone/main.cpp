#include <iostream>
#include "Game/Board.h"

using namespace N_Game;
int main()
{
    Board board(Difficulty::MEDIUM);

    board.displayBoard();
    return 0;
}