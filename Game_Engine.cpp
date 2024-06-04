#include "stdafx.h"
#include "Game_Engine.h"

Game_Engine::Game_Engine()
{
    this->Init_Window();
    this->Init_Best_Score();
    this->Init_Text();
    this->Set_Constant_Textures();
    this->Set_Menu_Textures();
}

void Game_Engine::Run()
{
    while (this->window.isOpen())
    {
        this->elapsed += this->clock.restart();
        this->time_per_frame = sf::seconds(1.f / this->speed);

        // CONTROLS
        this->Pull_Events();

        // WINDOW UPDATE
        this->window.clear(sf::Color::Transparent);
        this->Draw_Objects();
        this->window.display();
    }
}

//INITIALIZATION
void Game_Engine::Init_Text()
{
    //this->score_text = new Text_Elements(50.f, 60.f, std::to_string(this->score));
    if (!this->font.loadFromFile("font/OpenSans-Medium.ttf"))
    {
        std::cout << "Nie udalo sie zaladowac czcionki" << std::endl;
    }

    this->score_text.setFont(this->font);
    this->score_text.setString(std::to_string(this->score));
    this->score_text.setCharacterSize(46);
    this->score_text.setFillColor(sf::Color::White);
    this->score_text.setStyle(sf::Text::Regular);
    this->score_text.setPosition(100.f, 7.f);

    this->best_score_text.setFont(this->font);
    this->best_score_text.setString(this->best_score);
    this->best_score_text.setCharacterSize(46);
    this->best_score_text.setFillColor(sf::Color::White);
    this->best_score_text.setStyle(sf::Text::Regular);
    this->best_score_text.setPosition(240.f, 7.f);
}

void Game_Engine::Init_Window() // Wymiary okna : 565 x 625
{
    this->settings.antialiasingLevel = 8;
    this->window.create(sf::VideoMode(565, 625), "Snake", sf::Style::None, settings);
    this->window.setFramerateLimit(60);
    this->margins.cxLeftWidth = -1;
    SetWindowLong(this->window.getSystemHandle(), GWL_STYLE, WS_POPUP | WS_VISIBLE);
    sf::Image icon;
    icon.loadFromFile("texture/snake.png");
    window.setIcon(icon.getSize().x, icon.getSize().y, icon.getPixelsPtr());
}

void Game_Engine::Init_Best_Score()
{
    std::ifstream input("data/best_score.txt");
    std::getline(input, this->best_score);
    input.close();
}

//TEXTURES
void Game_Engine::Set_Constant_Textures()
{
    this->back_groud.push_back(new Texture_Manager(282.5f, 312.5f, 0.7882f, 400.f, 400.f, "texture/Tlo_Snake2.png", sf::Color(190, 190, 190, 255)));
    this->back_groud.push_back(new Texture_Manager(530.f, 35.f, 0.5f, 50.f, 50.f, "texture/close_button.png", sf::Color(190, 190, 190, 255)));
}

void Game_Engine::Set_Menu_Textures()
{
    this->free_elements.push_back(new Texture_Manager(282.5, 312.5, 0.5f, 200.f, 64.f, "texture/play_button.png", sf::Color(230, 230, 230, 255)));
    this->pause_button = new Texture_Manager(282.5, 312.5, 0.7f, 256.f, 256.f, "texture/pause.png", sf::Color(255, 255, 255, 255));
    this->winner = new Texture_Manager(282.5, 172.5, 0.4f, 256.f, 256.f, "texture/winner.png", sf::Color(255, 255, 255, 255));
}

void Game_Engine::Draw_Objects()
{
    for (size_t i = 0; i < back_groud.size(); i++)
    {
        this->back_groud[i]->Render(this->window);
    }
    this->window.draw(score_text);
    this->window.draw(best_score_text);
    for (size_t i = 0; i < this->free_elements.size(); i++)
    {
        this->free_elements[i]->Render(this->window);
    }
    if (this->Pause)
    {
        this->pause_button->Render(this->window);
    }
    if (this->WON)
    {
        this->winner->Render(this->window);
    }
}

void Game_Engine::Reset_Score()
{
    this->score = 0;
}
//KEYBOARD
void Game_Engine::Check_Keyboard()
{
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Escape))
    {
        this->window.close();
    }
    if (this->last_snake_direction != DIR::RIGHT)
    {
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A))
        {
            this->Pause = false;
        }
    }
    if (this->last_snake_direction != DIR::LEFT)
    {
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D))
        {
            this->Pause = false;
        }
    }
    if (this->last_snake_direction != DIR::UP)
    {
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S))
        {
            this->Pause = false;
        }
    }
    if (this->last_snake_direction != DIR::DOWN)
    {
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W))
        {
            this->Pause = false;
        }
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Space))
    {
        this->Pause = true;
    }
}

void Game_Engine::Pull_Events()
{
    sf::Event event;
    while (this->window.pollEvent(event))
    {
        if (!this->In_Menu)
        {
            this->Check_Keyboard();
        }
    }
}


