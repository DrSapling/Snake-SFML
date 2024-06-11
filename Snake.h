#pragma once
#include "RenderEngine.h"

class Snake : public RenderEngine
{
private:
    //Private member variables for textures, sprites, and positions
    sf::Texture texture_eye;
    sf::Texture texture_eye_ball;
    sf::Sprite eye;
    sf::Sprite eye_ballR;
    sf::Sprite eye_ballL;

    sf::Vector2f LEFT;
    sf::Vector2f RIGHT;

    sf::Vector2f LEFT_UP;
    sf::Vector2f RIGHT_UP;

    sf::Vector2f APPLE_POS;

    sf::Color color;
    sf::CircleShape circle;
    DEAD::Dead_Reason reason = DEAD::UNKNOWN;

    float x = 0;
    float y = 0;

    const float size = 32;

    bool face = false;
public:
    Snake(float x_arg, float y_arg, sf::Color color);
    Snake(float x_arg, float y_arg, sf::Color color, bool face_arg);
    ~Snake();

    void Move(sf::Vector2f vec); // Moves the snake segment
    sf::Vector2f GetSnakePosition(); // Gets the current position of the snake segment
    void SetSnakePosition(sf::Vector2f vec); // Sets the position of the snake segment
    void InitTextures() override;
    void InitSprite() override;
    void Render(sf::RenderTarget& target) override;
    void Render(sf::RenderTarget& target, DIR::Direction dir, DIR::Direction last) override;
    void Update(DIR::Direction dir, DIR::Direction last) override;
    void InitTextures(std::string path_arg) {};
    void Set_Eye_Rotation(int angle); // Set the rotation of the snake's eyes
    void Update_Apple_Position(sf::Vector2f pos); // Update the apple position for the snake's eyes
    float Designate_APPLE_EYE_Angle(float x_arg, float y_arg); // Calculate the angle for the eyes to follow the apple

    void SetDeadReason(DEAD::Dead_Reason reason_arg); // Sets the reason for the snake's death
    const DEAD::Dead_Reason GetDeadReason() const; // Gets the reason for the snake's death

    friend std::ostream& operator<<(std::ostream& os, const Snake& snake) // Overloaded output stream operator for Snake
    {
        switch (snake.GetDeadReason())
        {
        case DEAD::TAIL:
            return os << "Snake killed by his tail";
            break;
        case DEAD::WALL:
            return os << "Snake killed by wall";
            break;
        case DEAD::UNKNOWN:
            return os << "Unkown reason of death";
            break;
        }
    }
};

