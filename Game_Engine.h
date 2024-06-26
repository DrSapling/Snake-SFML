#pragma once
#include "Texture_Manager.h"
#include "Snake.h"
#include "Apple.h"
#include "BlueApple.h"

class Game_Engine
{
private:
    //Elements to create game window
    sf::ContextSettings settings;
    sf::RenderWindow window;
    MARGINS margins;

    //Class objects
    Texture_Manager obj;
    std::vector<Texture_Manager*> back_groud;
    std::vector<Texture_Manager*> free_elements;
    Texture_Manager* pause_button;
    Texture_Manager* winner;

    //SNAKE
    std::vector<Snake*> snake;
    DIR::Direction snake_direction = DIR::STOP;
    DIR::Direction last_snake_direction = DIR::RIGHT; //Initially snake can not go left
    sf::Vector2f last_position;
    sf::Vector2f last_position_2;
    float speed = 60;
    const float snake_speed = 4;
    bool Is_Snake_Dead = false;
    

    //APPLE
    Apple* apple;
    BlueApple* blue_apple;

    //COLISIONS
    std::vector<std::vector<int>> matrix;

    //TIME
    sf::Clock clock;
    sf::Time elapsed;
    sf::Time time_per_frame;

    //MENU STATE FLAGS
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
    void Run(); //Method to run the main game loop

    //INITIALIZATION
    void Init_Text();
    void Init_Replay_Menu();
    void Init_Window();
    void Set_Best_Score();
    void Init_Best_Score();

    //TEXTURES
    void Set_Constant_Textures();
    void Set_Menu_Textures();
    void Delete_Textures();
    void Draw_Objects();

    //SNAKE
    void Create_Snake();

        //MOVEMENT
        void Smooth_Snake_Motion();

        //QUESTIONS
        bool Is_Snake_On_The_Spot();
        bool Is_Snake_Outside();

        //FUNCTIONS
        void Touch_His_Body();
        void Reset_Game();
        void Reset_Score();
        void Increase_Snake_Length();
        void Kill_Snake();
    

    //APPLE
    void Apple_Eaten();
    void Create_Apple();
    void Create_Blue_Apple();

    //KEYBOARD
    void Check_Keyboard();
    void Pull_Events();
};

