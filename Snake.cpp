#include "Snake.h"

Snake::Snake(float x_arg, float y_arg, sf::Color color) // Include the header file for the Snake class
{
    this->x = x_arg;
    this->y = y_arg;
    this->circle.setOrigin(sf::Vector2f(this->size / 3, this->size / 3));
    this->circle.setPosition(sf::Vector2f(x_arg, y_arg)); // Set initial position and origin of the snake segment
    this->circle.setRadius(this->size/3); // Set radius and color of the snake segment
    this->circle.setFillColor(color);
}

Snake::Snake(float x_arg, float y_arg, sf::Color color, bool face_arg) // Constructor for the Snake class with position, color, and face flag
{
    // Initialize vectors for eye positions
    this->LEFT = sf::Vector2f(8.5f, 7.f);
    this->RIGHT = sf::Vector2f(-8.5f, 7.f);

    this->LEFT_UP = sf::Vector2f(7.f, -8.5f);
    this->RIGHT_UP = sf::Vector2f(7.f, 8.5f);

    this->face = face_arg; // Set the face flag for the snake
    this->x = x_arg;
    this->y = y_arg;
    this->circle.setOrigin(sf::Vector2f(this->size / 3, this->size / 3));
    this->circle.setPosition(sf::Vector2f(x_arg, y_arg)); // Set initial position and origin of the snake segment
    this->circle.setRadius(this->size / 3); // Set radius and color of the snake segment
    this->circle.setFillColor(color);
    this->InitTextures(); // Initialize the textures for the snake
    this->InitSprite(); // Initialize the sprite for the snake
}

Snake::~Snake()
{
    //std::cout << "Circle deleted" << std::endl;
}

void Snake::Move(sf::Vector2f vec) // Moves the snake segment
{
    this->x += vec.x;
    this->y += vec.y;
    this->circle.setPosition(this->x, this->y);
}

sf::Vector2f Snake::GetSnakePosition() // Gets the current position of the snake segment
{
    return sf::Vector2f(this->x, this->y);
}

void Snake::SetSnakePosition(sf::Vector2f vec) // Sets the position of the snake segment
{
    this->x = vec.x;
    this->y = vec.y;
    this->circle.setPosition(this->x, this->y);
}

void Snake::InitTextures() // Initialize the textures for the snake's eyes
{
    if (!this->texture_eye.loadFromFile("texture/eye.png")) // Check if the eye texture failed to load
    {
        std::cout << "Texture couldn't be loaded" << std::endl; // Print error
    }
    else
    {
        this->texture_eye.setSmooth(true); // Set the texture smoothing for the eye texture
    }
    if (!this->texture_eye_ball.loadFromFile("texture/eye_ball.png")) // Check if the eye ball texture failed to load
    {
        std::cout << "Texture couldn't be loaded" << std::endl; // Print error
    }
    else
    {
        this->texture_eye_ball.setSmooth(true); // Set the texture smoothing for the eye ball texture
    }
}

void Snake::InitSprite()
{
    this->eye.setTexture(this->texture_eye); // Initialize the sprite for the snake's eye
    this->eye.setOrigin(32.f, 32.f); // Set the texture and origin for the eye sprite
    this->eye.setScale(0.5f, 0.5f); // Set the scale and position for the eye sprite
    this->eye.setPosition(this->circle.getPosition());

    this->eye_ballR.setTexture(this->texture_eye_ball); // Initialize the sprite for the right eye ball
    this->eye_ballR.setOrigin(32.f, 32.f); // Set the texture and origin for the right eye ball sprite
    this->eye_ballR.setScale(0.25f, 0.25f); // Set the scale and position for the right eye ball sprite
    this->eye_ballR.setPosition(this->circle.getPosition() + RIGHT);

    this->eye_ballL.setTexture(this->texture_eye_ball); // Initialize the sprite for the left eye ball
    this->eye_ballL.setOrigin(32.f, 32.f); // Set the texture and origin for the left eye ball sprite
    this->eye_ballL.setScale(0.25f, 0.25f); // Set the scale and position for the left eye ball sprite
    this->eye_ballL.setPosition(this->circle.getPosition() - LEFT);
}

void Snake::Render(sf::RenderTarget& target) // Render snake segment to window
{
    target.draw(this->circle);
}

void Snake::Render(sf::RenderTarget& target, DIR::Direction dir, DIR::Direction last) // Render snake segment with direction to window
{
    this->Update(dir, last);  // Update the eye positions based on direction
    target.draw(this->circle);
    target.draw(this->eye); // Render the snake's eye and eye balls to the target
    target.draw(this->eye_ballR);
    target.draw(this->eye_ballL);
}

void Snake::Update(DIR::Direction dir, DIR::Direction last)
{
    switch (dir)
    {
    case DIR::LEFT:
        this->eye.setRotation(180);
        this->eye.setPosition(this->circle.getPosition());
        this->eye_ballR.setPosition(this->circle.getPosition() - RIGHT);
        this->eye_ballL.setPosition(this->circle.getPosition() + LEFT);
        this->eye_ballR.setRotation(this->Designate_APPLE_EYE_Angle(this->eye_ballR.getPosition().x, this->eye_ballR.getPosition().y));
        this->eye_ballL.setRotation(this->Designate_APPLE_EYE_Angle(this->eye_ballL.getPosition().x, this->eye_ballL.getPosition().y));
        break;
    case DIR::RIGHT:
        this->eye.setRotation(0);
        this->eye.setPosition(this->circle.getPosition());
        this->eye_ballR.setPosition(this->circle.getPosition() + RIGHT);
        this->eye_ballL.setPosition(this->circle.getPosition() - LEFT);
        this->eye_ballR.setRotation(this->Designate_APPLE_EYE_Angle(this->eye_ballR.getPosition().x, this->eye_ballR.getPosition().y));
        this->eye_ballL.setRotation(this->Designate_APPLE_EYE_Angle(this->eye_ballL.getPosition().x, this->eye_ballL.getPosition().y));
        break;
    case DIR::UP:
        this->eye.setRotation(270);
        this->eye.setPosition(this->circle.getPosition());
        this->eye_ballR.setPosition(this->circle.getPosition() - LEFT_UP);
        this->eye_ballL.setPosition(this->circle.getPosition() + RIGHT_UP);
        this->eye_ballR.setRotation(this->Designate_APPLE_EYE_Angle(this->eye_ballR.getPosition().x, this->eye_ballR.getPosition().y));
        this->eye_ballL.setRotation(this->Designate_APPLE_EYE_Angle(this->eye_ballL.getPosition().x, this->eye_ballL.getPosition().y));
        break;
    case DIR::DOWN:
        this->eye.setRotation(90);
        this->eye.setPosition(this->circle.getPosition());
        this->eye_ballR.setPosition(this->circle.getPosition() + LEFT_UP);
        this->eye_ballL.setPosition(this->circle.getPosition() - RIGHT_UP);
        this->eye_ballR.setRotation(this->Designate_APPLE_EYE_Angle(this->eye_ballR.getPosition().x, this->eye_ballR.getPosition().y));
        this->eye_ballL.setRotation(this->Designate_APPLE_EYE_Angle(this->eye_ballL.getPosition().x, this->eye_ballL.getPosition().y));
        break;
    case DIR::STOP:
        if (last == DIR::LEFT)
        {
            this->eye.setRotation(180);
            this->eye.setPosition(this->circle.getPosition());
            this->eye_ballR.setPosition(this->circle.getPosition() - RIGHT);
            this->eye_ballL.setPosition(this->circle.getPosition() + LEFT);
            this->eye_ballR.setRotation(this->Designate_APPLE_EYE_Angle(this->eye_ballR.getPosition().x, this->eye_ballR.getPosition().y));
            this->eye_ballL.setRotation(this->Designate_APPLE_EYE_Angle(this->eye_ballL.getPosition().x, this->eye_ballL.getPosition().y));
        }
        else if (last == DIR::RIGHT)
        {
            this->eye.setRotation(0);
            this->eye.setPosition(this->circle.getPosition());
            this->eye_ballR.setPosition(this->circle.getPosition() + RIGHT);
            this->eye_ballL.setPosition(this->circle.getPosition() - LEFT);
            this->eye_ballR.setRotation(this->Designate_APPLE_EYE_Angle(this->eye_ballR.getPosition().x, this->eye_ballR.getPosition().y));
            this->eye_ballL.setRotation(this->Designate_APPLE_EYE_Angle(this->eye_ballL.getPosition().x, this->eye_ballL.getPosition().y));
        }
        else if (last == DIR::UP)
        {
            this->eye.setRotation(270);
            this->eye.setPosition(this->circle.getPosition());
            this->eye_ballR.setPosition(this->circle.getPosition() - LEFT_UP);
            this->eye_ballL.setPosition(this->circle.getPosition() + RIGHT_UP);
            this->eye_ballR.setRotation(this->Designate_APPLE_EYE_Angle(this->eye_ballR.getPosition().x, this->eye_ballR.getPosition().y));
            this->eye_ballL.setRotation(this->Designate_APPLE_EYE_Angle(this->eye_ballL.getPosition().x, this->eye_ballL.getPosition().y));
        }
        else if (last == DIR::DOWN)
        {
            this->eye.setRotation(90);
            this->eye.setPosition(this->circle.getPosition());
            this->eye_ballR.setPosition(this->circle.getPosition() + LEFT_UP);
            this->eye_ballL.setPosition(this->circle.getPosition() - RIGHT_UP);
            this->eye_ballR.setRotation(this->Designate_APPLE_EYE_Angle(this->eye_ballR.getPosition().x, this->eye_ballR.getPosition().y));
            this->eye_ballL.setRotation(this->Designate_APPLE_EYE_Angle(this->eye_ballL.getPosition().x, this->eye_ballL.getPosition().y));
        }
        break;
    }
}

void Snake::Set_Eye_Rotation(int angle) // Set the rotation of the snake's eyes
{
    this->eye.setRotation(angle);
}

void Snake::Update_Apple_Position(sf::Vector2f pos) // Update the apple position for the snake's eyes
{
    this->APPLE_POS = pos;
}

float Snake::Designate_APPLE_EYE_Angle(float x_arg, float y_arg) // Calculate the angle for the eyes to follow the apple
{
    if (this->APPLE_POS.x < x_arg && this->APPLE_POS.y > y_arg) // Angle for apple BELOW LEFT of the eye
    {
        float x = std::abs(this->APPLE_POS.x - x_arg);
        float y = std::abs(this->APPLE_POS.y - y_arg);
        return (std::atan(y / x) * 180.0f / 3.14f) + 90;
    }
    else if(this->APPLE_POS.x < x_arg && this->APPLE_POS.y < y_arg) // Angle for apple ABOVE LEFT of the eye
    {
        float x = std::abs(this->APPLE_POS.x - x_arg);
        float y = std::abs(this->APPLE_POS.y - y_arg);
        return (std::atan(y / x) * 180.0f / 3.14f) + 180;
    }
    else if (this->APPLE_POS.x > x_arg && this->APPLE_POS.y < y_arg) // Angle for apple ABOVE RIGHT of the eye
    {
        float x = std::abs(this->APPLE_POS.x - x_arg);
        float y = std::abs(this->APPLE_POS.y - y_arg);
        return (std::atan(y / x) * 180.0f / 3.14f) + 270.f;
    }
    else if (this->APPLE_POS.x > x_arg && this->APPLE_POS.y > y_arg) // Angle for apple BELOW RIGHT of the eye
    {
        float x = std::abs(this->APPLE_POS.x - x_arg);
        float y = std::abs(this->APPLE_POS.y - y_arg);
        return (std::atan(y / x) * 180.0f / 3.14f);
    }
}

void Snake::SetDeadReason(DEAD::Dead_Reason reason_arg)  // Sets the reason for the snake's death
{
    this->reason = reason_arg;
}

const DEAD::Dead_Reason Snake::GetDeadReason() const  // Gets the reason for the snake's death
{
    return this->reason;
}
