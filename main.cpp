#include "Game_Engine.h"

int main()
{
    srand(static_cast<unsigned>(time(0))); //Seed the random number generator with the current time
    Game_Engine game; //Create an instance of the Game_Engine class

    game.Run(); //Run the main game loop

    return 0;
}
