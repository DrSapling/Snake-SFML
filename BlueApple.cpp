#include "BlueApple.h"

BlueApple::BlueApple()
{
    this->InitTextures();
    this->InitSprite();
    this->Generate_Position();
    std::cout << "Blue Apple created" << std::endl;
}

void BlueApple::InitTextures()
{
    if (!this->texture.loadFromFile("texture/blueapple.png")) // Ensure you have this texture in your assets
    {
        std::cout << "Couldn't load blue apple texture" << "\n";
    }
    else
    {
        this->texture.setSmooth(true);
    }
}