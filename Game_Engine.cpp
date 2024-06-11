#include "Game_Engine.h"

Game_Engine::Game_Engine()
{
    this->Init_Window(); // Initialize the game window
    this->Init_Best_Score(); // Initialize the best score
    this->Init_Text(); // Initialize the text elements
    this->Set_Constant_Textures(); // Set constant textures for the game
    this->Set_Menu_Textures(); // Set textures for the menu
    this->Create_Snake(); // Create the snake
    this->Create_Apple(); // Create the apple
    this->Is_Snake_On_The_Spot(); // Check if the snake is on the spot
}

void Game_Engine::Run() // Main game loop
{
    while (this->window.isOpen())
    {
        this->elapsed += this->clock.restart(); // Restart the clock and update elapsed time
        this->time_per_frame = sf::seconds(1.f / this->speed); // Define the time per frame based on speed

        // CONTROLS
        this->Pull_Events(); // Handle user input events

        // SNAKE MOVEMENT
        if (this->elapsed >= this->time_per_frame) // Update snake movement if enough time has passed
        {
            this->Smooth_Snake_Motion();
            this->elapsed -= this->time_per_frame;
        }

        // MENU ODRADZANIA
        if (this->Is_Snake_Dead) // Handle game over menu if the snake is dead
        {
            this->Init_Replay_Menu();
            this->Is_Snake_Dead = false;
            this->In_Menu = true;
            this->Reset_Game(); // Reset game and display the replay menu
        }
        // WINDOW UPDATE
        this->window.clear(sf::Color::Transparent); // Clear the window with a transparent color
        this->Draw_Objects(); // Draw all game objects
        this->window.display(); // Display the updated window
    }
}

//INITIALIZATION
void Game_Engine::Init_Text() // Initialize text elements
{
    //this->score_text = new Text_Elements(50.f, 60.f, std::to_string(this->score));
    if (!this->font.loadFromFile("font/OpenSans-Medium.ttf")) // Check if the font failed to load
    {
        std::cout << "Nie udalo sie zaladowac czcionki" << std::endl;
    }

    this->score_text.setFont(this->font); // Set properties for the best score text
    this->score_text.setString(std::to_string(this->score));
    this->score_text.setCharacterSize(46);
    this->score_text.setFillColor(sf::Color::White);
    this->score_text.setStyle(sf::Text::Regular);
    this->score_text.setPosition(100.f, 7.f);

    this->best_score_text.setFont(this->font); // Set properties for the best score text
    this->best_score_text.setString(this->best_score);
    this->best_score_text.setCharacterSize(46);
    this->best_score_text.setFillColor(sf::Color::White);
    this->best_score_text.setStyle(sf::Text::Regular);
    this->best_score_text.setPosition(240.f, 7.f);
}

void Game_Engine::Init_Replay_Menu() // Initialize the replay menu
{
    this->free_elements.push_back(new Texture_Manager(282.5, 312.5, 0.5f, 200.f, 64.f, "texture/replay_button.png", sf::Color(230, 230, 230, 255))); // Add a replay button to the free elements
}

void Game_Engine::Init_Window() // Initialize the game window with specific settings
{
    this->settings.antialiasingLevel = 8; // Set the antialiasing level for smoother graphics
    this->window.create(sf::VideoMode(565, 625), "Snake", sf::Style::None, settings); // Create the game window
    this->window.setFramerateLimit(60); // Set the frame rate limit for the window
    this->margins.cxLeftWidth = -1;
    SetWindowLong(this->window.getSystemHandle(), GWL_STYLE, WS_POPUP | WS_VISIBLE); // Remove window frame for a borderless window
    sf::Image icon;
    icon.loadFromFile("texture/snake.png"); // Load the window icon
    window.setIcon(icon.getSize().x, icon.getSize().y, icon.getPixelsPtr()); // Set the icon for the window
}

void Game_Engine::Set_Best_Score() // Set the best score if the current score is higher
{
    if (std::stoi(this->best_score) <= this->score)
    {
        std::ofstream out("data/best_score.txt", std::ios::trunc);
        out << std::to_string(this->score); // Write the new best score to a file
        out.close(); 
    }
    this->Init_Best_Score();
    this->best_score_text.setString(this->best_score);
}

void Game_Engine::Init_Best_Score() // Initialize the best score from the file
{
    std::ifstream input("data/best_score.txt"); // Read the best score from the file
    std::getline(input, this->best_score);
    input.close();
}

//TEXTURES
void Game_Engine::Set_Constant_Textures() // Set constant textures for the background and close button
{
    this->back_groud.push_back(new Texture_Manager(282.5f, 312.5f, 0.7882f, 400.f, 400.f, "texture/Tlo_Snake2.png", sf::Color(190, 190, 190, 255)));
    this->back_groud.push_back(new Texture_Manager(530.f, 35.f, 0.5f, 50.f, 50.f, "texture/close_button.png", sf::Color(190, 190, 190, 255)));
}

void Game_Engine::Set_Menu_Textures() // Set menu textures for play, pause, and winner
{
    this->free_elements.push_back(new Texture_Manager(282.5, 312.5, 0.5f, 200.f, 64.f, "texture/play_button.png", sf::Color(230, 230, 230, 255)));
    this->pause_button = new Texture_Manager(282.5, 312.5, 0.7f, 256.f, 256.f, "texture/pause.png", sf::Color(255, 255, 255, 255));
    this->winner = new Texture_Manager(282.5, 172.5, 0.4f, 256.f, 256.f, "texture/winner.png", sf::Color(255, 255, 255, 255));
}

void Game_Engine::Delete_Textures()
{
    for (size_t i = 0; i < free_elements.size(); i++)
    {
        delete this->free_elements[i]; // Delete dynamically allocated textures
    }
}

void Game_Engine::Draw_Objects() // Draw all game objects to the window
{
    for (size_t i = 0; i < back_groud.size(); i++)
    {
        this->back_groud[i]->Render(this->window); // Draw the background elements
    }
    this->window.draw(score_text); // Draw the score and best score text
    this->window.draw(best_score_text);
    this->apple->Render(this->window);
    for (size_t i = 1; i < this->snake.size(); i++) // Draw the apple
    {
        this->snake[i]->Render(this->window); // Draw the snake segments
    }
    this->snake[0]->Render(this->window, this->snake_direction, this->last_snake_direction); // Draw the snake head with the current direction
    for (size_t i = 0; i < this->free_elements.size(); i++)
    {
        this->free_elements[i]->Render(this->window); // Draw additional elements like menu buttons
    }
    if (this->Pause)
    {
        this->pause_button->Render(this->window); // Draw the pause button if the game is paused
    }
    if (this->WON)
    {
        this->winner->Render(this->window); // Draw the winner texture if the game is won
    }
}

//SNAKE
void Game_Engine::Create_Snake() // Create the initial snake with multiple segments at x = 298.5, y = 325.5 (42.7, 101.7)
{
    this->snake.push_back(new Snake(298.7f, 325.7f, sf::Color(84, 118, 229), true));
    this->snake.push_back(new Snake(294.7f, 325.7f, sf::Color(84, 118, 229)));
    this->snake.push_back(new Snake(290.7f, 325.7f, sf::Color(84, 118, 229)));
    this->snake.push_back(new Snake(286.7f, 325.7f, sf::Color(84, 118, 229)));
}

//MOVEMENT
void Game_Engine::Smooth_Snake_Motion() // Smooth snake movement based on direction
{
    if (this->score >= 256) // Check if the snake has reached the winning score
    {
        this->snake_direction = DIR::STOP;
        this->last_snake_direction = DIR::STOP;
        this->Is_Snake_Dead = true;
        this->WON = true;
    }
    if (this->Is_Snake_Outside()) // Check if the snake is outside the game area
    {
        this->snake_direction = DIR::STOP;
        this->last_snake_direction = DIR::STOP;
        this->Is_Snake_Dead = true;
    }
    if (this->score > 4)
    {
        this->Touch_His_Body(); // Check for collisions with the snake's body
    }
    if (this->Is_Snake_On_The_Spot()) // Check if the snake is on the spot for movement
    {
        switch (this->snake_direction)
        {
        case DIR::LEFT:
            this->last_position = this->snake[0]->GetSnakePosition();
            this->snake[0]->Move(sf::Vector2f(-this->snake_speed, 0.f));
            for (size_t i = 1; i < this->snake.size(); ++i)
            {
                this->last_position_2 = this->snake[i]->GetSnakePosition();
                this->snake[i]->SetSnakePosition(this->last_position);
                this->last_position = this->last_position_2;
            }
            this->last_snake_direction = DIR::LEFT;
            break;

        case DIR::RIGHT:
            this->last_position = this->snake[0]->GetSnakePosition();
            this->snake[0]->Move(sf::Vector2f(this->snake_speed, 0.f));
            for (size_t i = 1; i < this->snake.size(); ++i)
            {
                this->last_position_2 = this->snake[i]->GetSnakePosition();
                this->snake[i]->SetSnakePosition(this->last_position);
                this->last_position = this->last_position_2;
            }
            this->last_snake_direction = DIR::RIGHT;
            break;

        case DIR::UP:
            this->last_position = this->snake[0]->GetSnakePosition();
            this->snake[0]->Move(sf::Vector2f(0.f, -this->snake_speed));
            for (size_t i = 1; i < this->snake.size(); ++i)
            {
                this->last_position_2 = this->snake[i]->GetSnakePosition();
                this->snake[i]->SetSnakePosition(this->last_position);
                this->last_position = this->last_position_2;
            }
            this->last_snake_direction = DIR::UP;
            break;

        case DIR::DOWN:
            this->last_position = this->snake[0]->GetSnakePosition();
            this->snake[0]->Move(sf::Vector2f(0.f, this->snake_speed));
            for (size_t i = 1; i < this->snake.size(); ++i)
            {
                this->last_position_2 = this->snake[i]->GetSnakePosition();
                this->snake[i]->SetSnakePosition(this->last_position);
                this->last_position = this->last_position_2;
            }
            this->last_snake_direction = DIR::DOWN;
            break;

        case DIR::STOP:
            break;
        }
    }
    else
    {
        switch (this->last_snake_direction) // Handle movement for each direction
        {
        case DIR::LEFT:
            this->last_position = this->snake[0]->GetSnakePosition();
            this->snake[0]->Move(sf::Vector2f(-this->snake_speed, 0.f));
            for (size_t i = 1; i < this->snake.size(); ++i)
            {
                this->last_position_2 = this->snake[i]->GetSnakePosition();
                this->snake[i]->SetSnakePosition(this->last_position);
                this->last_position = this->last_position_2;
            }
            break;

        case DIR::RIGHT:
            this->last_position = this->snake[0]->GetSnakePosition();
            this->snake[0]->Move(sf::Vector2f(this->snake_speed, 0.f));
            for (size_t i = 1; i < this->snake.size(); ++i)
            {
                this->last_position_2 = this->snake[i]->GetSnakePosition();
                this->snake[i]->SetSnakePosition(this->last_position);
                this->last_position = this->last_position_2;
            }
            break;

        case DIR::UP:
            this->last_position = this->snake[0]->GetSnakePosition();
            this->snake[0]->Move(sf::Vector2f(0.f, -this->snake_speed));
            for (size_t i = 1; i < this->snake.size(); ++i)
            {
                this->last_position_2 = this->snake[i]->GetSnakePosition();
                this->snake[i]->SetSnakePosition(this->last_position);
                this->last_position = this->last_position_2;
            }
            break;

        case DIR::DOWN:
            this->last_position = this->snake[0]->GetSnakePosition();
            this->snake[0]->Move(sf::Vector2f(0.f, this->snake_speed));
            for (size_t i = 1; i < this->snake.size(); ++i)
            {
                this->last_position_2 = this->snake[i]->GetSnakePosition();
                this->snake[i]->SetSnakePosition(this->last_position);
                this->last_position = this->last_position_2;
            }
            break;

        case DIR::STOP:
            break;
        }
    }
    this->Apple_Eaten(); // Handle eating the apple
}

//QUESTIONS
bool Game_Engine::Is_Snake_On_The_Spot()
{
    for (int i = 0; i < 16; ++i)
    {
        if (static_cast<int>(this->snake[0]->GetSnakePosition().x) == i * 32 + 42) // Check if the snake is on the spot for movement
        {
            for (int j = 0; j < 16; ++j)
            {
                if (static_cast<int>(this->snake[0]->GetSnakePosition().y) == j * 32 + 101) // Check if the snake's position matches grid coordinates
                {
                    return true;
                }
            }
        }
    }
    return false;
}

bool Game_Engine::Is_Snake_Outside()
{
    if(this->snake[0]->GetSnakePosition().x > 522.7f || this->snake[0]->GetSnakePosition().x < 42.7f || this->snake[0]->GetSnakePosition().y > 581.7f || this->snake[0]->GetSnakePosition().y < 101.7f) // Check if the snake's head is outside the game area
    {
        this->snake[0]->SetDeadReason(DEAD::WALL); // Set the reason for the snake's death
        std::cout << *this->snake[0] << std::endl; // Print the reason for the snake's death
        this->Set_Best_Score(); // Update the best score
        return true;
    }
    return false;
}

//FUNCTIONS
void Game_Engine::Touch_His_Body() // Check if the snake collided with its body
{
    for (size_t i = 16; i < this->snake.size(); ++i)
    {
        sf::Vector2f diff = this->snake[0]->GetSnakePosition() - this->snake[i]->GetSnakePosition(); 
        float distance = std::sqrt(diff.x * diff.x + diff.y * diff.y); // Calculate the distance between head and body segment
        if (distance <= 21.37f)
        {
            this->snake[0]->SetDeadReason(DEAD::TAIL); // Set the reason for the snake's death
            this->snake_direction = DIR::STOP;
            this->last_snake_direction = DIR::STOP;
            this->Set_Best_Score(); // Update the best score
            std::cout << *this->snake[0] << std::endl;
            this->Is_Snake_Dead = true;
        }
    }
}

void Game_Engine::Reset_Game()
{
    this->Kill_Snake();
    this->Reset_Score(); // Reset the game state
}

void Game_Engine::Reset_Score()
{
    this->score = 0; // Reset the score to zero
}

void Game_Engine::Increase_Snake_Length() // Increase the snake length by adding segments
{
    this->snake.push_back(new Snake(this->last_position_2.x, last_position_2.y, sf::Color(84, 118, 229)));
    this->snake.push_back(new Snake(this->last_position_2.x, last_position_2.y, sf::Color(84, 118, 229)));
    this->snake.push_back(new Snake(this->last_position_2.x, last_position_2.y, sf::Color(84, 118, 229)));
    this->snake.push_back(new Snake(this->last_position_2.x, last_position_2.y, sf::Color(84, 118, 229)));
    this->snake.push_back(new Snake(this->last_position_2.x, last_position_2.y, sf::Color(84, 118, 229)));
    this->snake.push_back(new Snake(this->last_position_2.x, last_position_2.y, sf::Color(84, 118, 229)));
    this->snake.push_back(new Snake(this->last_position_2.x, last_position_2.y, sf::Color(84, 118, 229)));
    this->snake.push_back(new Snake(this->last_position_2.x, last_position_2.y, sf::Color(84, 118, 229)));
}

void Game_Engine::Kill_Snake()
{
    for (size_t i = 0; i < this->snake.size(); ++i)
    {
        delete this->snake[i]; // Delete all snake segments
    }
    this->snake.clear(); // Clear the snake vector
    this->Create_Snake(); // Recreate the initial snake
}

//APPLE
void Game_Engine::Apple_Eaten() // Handle eating the apple
{
    sf::Vector2f diff = this->apple->GetPosition() - this->snake[0]->GetSnakePosition();
    float distance = std::sqrt(diff.x * diff.x + diff.y * diff.y); // Calculate the distance between snake and apple
    if (distance <= 25.f)
    {
        std::cout << "Deleted apple on position :" << *this->apple << std::endl;
        this->apple->Generate_Position(); // Generate a new position for the apple
        this->snake[0]->Update_Apple_Position(this->apple->GetPosition()); // Update the apple's position in the snake
        std::cout << "Created apple on position :" << *this->apple << std::endl;
        this->Increase_Snake_Length(); // Increase the snake's length and update score
        this->score += 1.f;
        this->score_text.setString(std::to_string(this->score));
    }
    if (std::to_string(this->score) > this->best_score)
    {
        this->Set_Best_Score(); // Set the best score if needed
    }
}

void Game_Engine::Create_Apple()
{
    this->apple = new Apple(); // Create a new apple
    this->snake[0]->Update_Apple_Position(this->apple->GetPosition()); // Update the apple's position in the snake
}

//KEYBOARD
void Game_Engine::Check_Keyboard() // Handle keyboard input for game controls
{
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Escape)) // Check if the escape key is pressed to close the game
    {
        this->window.close();
    }
    if (this->last_snake_direction != DIR::RIGHT)
    {
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A)) // Check if 'A' key is pressed to move left
        {
            this->snake_direction = DIR::LEFT;
            this->Pause = false;
        }
    }
    if (this->last_snake_direction != DIR::LEFT)
    {
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D)) // Check if 'D' key is pressed to move right
        {
            this->snake_direction = DIR::RIGHT;
            this->Pause = false;
        }
    }
    if (this->last_snake_direction != DIR::UP) // Check if 'S' key is pressed to move down
    {
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S))
        {
            this->snake_direction = DIR::DOWN;
            this->Pause = false;
        }
    }
    if (this->last_snake_direction != DIR::DOWN) // Check if 'W' key is pressed to move up
    {
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W))
        {
            this->snake_direction = DIR::UP;
            this->Pause = false;
        }
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Space)) // Check if space bar is pressed to pause the game
    {
        this->Pause = true;
        this->snake_direction = DIR::STOP;
    }
}

void Game_Engine::Pull_Events() // Handle all input events
{
    sf::Event event;
    while (this->window.pollEvent(event))
    {
        if (!this->In_Menu) // Check if the game is not in menu mode
        {
            this->Check_Keyboard(); // Handle keyboard input
        }
        // Handle mouse events for closing the window
        if (this->back_groud[1]->GetGlobalBounds().contains(this->window.mapPixelToCoords(sf::Mouse::getPosition(this->window))) && event.type == sf::Event::MouseButtonPressed)
        {
            this->window.close();
        }
        if (this->In_Menu) // Handle mouse events for starting the game
        {
            if (this->free_elements[0]->GetGlobalBounds().contains(this->window.mapPixelToCoords(sf::Mouse::getPosition(this->window))) && event.type == sf::Event::MouseButtonPressed)
            {
                this->WON = false;
                this->In_Menu = false;
                this->back_groud[0]->SetColor(sf::Color(255, 255, 255, 255));
                delete this->free_elements[0];
                this->free_elements.clear();
            }
        }
        // Handle mouse events for button hover effects
        if (this->back_groud[1]->GetGlobalBounds().contains(this->window.mapPixelToCoords(sf::Mouse::getPosition(this->window))))
        {
            this->back_groud[1]->SetColor(sf::Color(255, 255, 255, 255));
        }
        else
        {
            this->back_groud[1]->SetColor(sf::Color(190, 190, 190, 255));
        }
        if (this->In_Menu)
        {
            if (this->free_elements[0]->GetGlobalBounds().contains(this->window.mapPixelToCoords(sf::Mouse::getPosition(this->window))))
            {
                this->free_elements[0]->SetColor(sf::Color(255, 255, 255, 255));
            }
            else
            {
                this->free_elements[0]->SetColor(sf::Color(190, 190, 190, 255));
            }
        }
    }
}


