#pragma once

#include <iostream>
#include <SFML/Graphics.hpp>
#include <vector>
#include "towers/Tower.h"

class Level
{
private:
    sf::RenderWindow *window;
    sf::Texture backgroundTexture;
    sf::Sprite backgroundSprite;
    sf::Clock globalClock;

    std::vector<Tower *> towers;

public:
    Level(sf::RenderWindow &window);
    void loadBackground();
    void update();
};