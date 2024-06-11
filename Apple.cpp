#include "Apple.h"


Apple::Apple()
{
    this->InitTextures(); // Initialize the textures for the apple
    this->InitSprite(); // Initialize the sprite for the apple
    this->Generate_Position(); // Generate a random position for the apple
    std::cout << "Apple created" << std::endl; // Print a message indicating apple creation
}

void Apple::InitTextures() // Initialize textures for the apple
{
    if (!this->texture.loadFromFile("texture/apple.png")) // Check if the texture failed to load
    {
        std::cout << "Couldn't load texture" << "\n"; // Print error
    }
    else
    {
        this->texture.setSmooth(true); // Initialize the sprite with the texture
    }
}

void Apple::InitSprite()  // Initialize the sprite with the texture
{
    this->sprite.setTexture(this->texture);
    this->sprite.setOrigin(225.f, 225.f); // Set the origin of the sprite
    this->sprite.setScale(this->scale, this->scale); // Set the scale of the sprite
}

void Apple::Render(sf::RenderTarget& target) // Render the apple sprite to the target
{
    target.draw(this->sprite);
}

const sf::Vector2f Apple::GetPosition() const
{
    return this->sprite.getPosition(); // Get the position of the apple sprite
}

void Apple::Generate_Position() // Generate a random position for the apple
{
    float x = std::rand() % 16; // random x and y position within the grid
    float y = std::rand() % 16;
    this->sprite.setPosition(32.f * x + 42.7f, 32.f * y + 101.7f); // Set the position of the apple sprite
}



