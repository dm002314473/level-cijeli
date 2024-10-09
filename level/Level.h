#pragma once

#include <iostream>
#include <SFML/Graphics.hpp>

class Level
{
private:
    sf::RenderWindow *window;
    sf::Texture backgroundTexture;
    sf::Sprite backgroundSprite;
    sf::Clock globalClock;

public:
    Level(sf::RenderWindow &window);
    void loadBackground();
    void update();
};