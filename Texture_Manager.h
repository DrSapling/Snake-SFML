#pragma once

class Texture_Manager : public RenderEngine
{
private:
    sf::Texture texture;
    sf::Sprite sprite;
public:
    Texture_Manager(float x_pos, float y_pos, float scale, float size_x, float size_y, std::string file_path, sf::Color color);
    ~Texture_Manager();

    void InitTextures(std::string path_arg) override;
};

