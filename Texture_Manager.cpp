#include "Texture_Manager.h"

Texture_Manager::Texture_Manager(float x_pos, float y_pos, float scale, float size_x, float size_y, std::string file_path) // Constructor with parameters for position, scale, size, and file path
{
    this->InitTextures(file_path); // Initialize the texture from the file path
    this->sprite.setTexture(this->texture); // Set the texture for the sprite
    this->sprite.setOrigin(size_x, size_y); // Set the origin of the sprite
    this->sprite.setScale(scale, scale); // Set the scale of the sprite
    this->sprite.setPosition(x_pos, y_pos); // Set the position of the sprite
    std::cout << "Texture created" << std::endl; // Print a message indicating texture creation
}

Texture_Manager::Texture_Manager(float x_pos, float y_pos, float scale, float size_x, float size_y, std::string file_path, sf::Color color) //
    this->InitTextures(file_path); // Initialize the texture from the file path
    this->sprite.setTexture(this->texture); // Set the texture for the sprite
    this->sprite.setOrigin(size_x, size_y); // Set the origin of the sprite
    this->sprite.setScale(scale, scale); // Set the scale of the sprite
    this->sprite.setPosition(x_pos, y_pos); // Set the position of the sprite
    this->sprite.setColor(color); // Set the color of the sprite
    std::cout << "Texture created" << std::endl; // Print a message indicating texture creation
}

Texture_Manager::~Texture_Manager()
{
    std::cout << "Texture deleted" << std::endl; // Print a message indicating texture deletion
}

void Texture_Manager::InitTextures(std::string path_arg) // Initialize texture from a given file path
{
    if (!this->texture.loadFromFile(path_arg)) // Check if the texture failed to load
    {
        std::cout << "Texture from path: " << path_arg << " couldn't be loaded" << std::endl; // Print error
    }
    else
    {
        this->texture.setSmooth(true); // Set the texture smoothing
    }
}

void Texture_Manager::Render(sf::RenderTarget& target) // Render the sprite to the target
{
    target.draw(this->sprite);
}

sf::FloatRect Texture_Manager::GetGlobalBounds() // Get the global bounds of the sprite
{
    return this->sprite.getGlobalBounds();
}

void Texture_Manager::SetColor(sf::Color color) // Set the color of the sprite
{
    this->sprite.setColor(color);
}
