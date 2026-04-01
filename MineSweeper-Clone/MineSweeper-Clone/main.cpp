#include <iostream>
#include "Game/Gameplay.h"

using namespace N_Game;

int main()
{
    // Create Gameplay controller (handles full game lifecycle)
    Gameplay game;

    // Start the main game loop
    game.run();

    return 0;
}