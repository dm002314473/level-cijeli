#pragma once

#include <iostream>
#include <SFML/Graphics.hpp>

class Tower
{
protected:
    sf::Texture towerTexture;
    sf::Sprite towerSprite;

public:
    Tower();
    void loadImage();
    virtual void upgrade();

    virtual void action(sf::Time currentTime) = 0;

    void draw(sf::RenderWindow &window);
};