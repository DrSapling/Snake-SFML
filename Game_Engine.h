#pragma once
#include "Texture_Manager.h"

class Game_Engine
{
private:
    //Elements to create window
    sf::ContextSettings settings;
    sf::RenderWindow window;
    MARGINS margins;

    //TIME
    sf::Clock clock;
    sf::Time elapsed;
    sf::Time time_per_frame;

public:
    Game_Engine();
    void Run();

    //INITIALIZATION
    void Init_Window();
};

