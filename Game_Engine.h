#pragma once
#include "Texture_Manager.h"

class Game_Engine
{
private:
    //Elements to create window
    sf::ContextSettings settings;
    sf::RenderWindow window;
    MARGINS margins;

    //Class objects
    Texture_Manager obj;
    std::vector<Texture_Manager*> back_groud;
    std::vector<Texture_Manager*> free_elements;
    Texture_Manager* pause_button;
    Texture_Manager* winner;

    //TIME
    sf::Clock clock;
    sf::Time elapsed;
    sf::Time time_per_frame;

public:
    Game_Engine();
    void Run();

    //INITIALIZATION
    void Init_Window();

    //TEXTURES
    void Set_Constant_Textures();
    void Set_Menu_Textures();
};

