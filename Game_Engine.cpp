#include "Game_Engine.h"

Game_Engine::Game_Engine()
{
    this->Init_Window();
    this->Set_Constant_Textures();
    this->Set_Menu_Textures();
}

void Game_Engine::Run()
{
    while (this->window.isOpen())
    {
        this->elapsed += this->clock.restart();
        this->time_per_frame = sf::seconds(1.f / this->speed);

        // WINDOW UPDATE
        this->window.clear(sf::Color::Transparent);
        this->window.display();
    }
}

//INITIALIZATION
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
