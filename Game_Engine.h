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

    //MENU
    bool In_Menu = true;
    bool Pause = false;
    bool WON = false;

    //SCORE
    sf::Text score_text, best_score_text;
    sf::Font font;
    int score = 0;
    std::string best_score;

public:
    Game_Engine();
    void Run();

    //INITIALIZATION
    void Init_Window();
    void Init_Best_Score();

    //TEXTURES
    void Set_Constant_Textures();
    void Set_Menu_Textures();
};

