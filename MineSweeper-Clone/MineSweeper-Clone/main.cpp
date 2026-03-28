#include <iostream>
#include "Game/Cell.h"

using namespace N_Game;
int main()
{
    Cell cell;
    std::cout << "Cell holds : " << cell.getCellDisplayString() << std::endl;

    cell.setCellState(CellState::FLAGGED);

    std::cout << "Cell holds : " << cell.getCellDisplayString() << std::endl;

    cell.setCellState(CellState::OPEN);
    cell.setCellType(CellType::MINE);

    std::cout << "Cell holds : " << cell.getCellDisplayString() << std::endl;

    return 0;
}