#include "Game_Engine.h"

Game_Engine::Game_Engine()
{
    this->Init_Window();
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

