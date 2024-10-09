#include "Tower.h"

Tower::Tower()
{
    std::cout << "Tower constructed!" << std::endl;
    loadImage();
}

void Tower::loadImage()
{
    if (!towerTexture.loadFromFile("level\\images\\background.jpeg"))
        std::cerr << "Failed to load tower texture from level\\images\\background.jpeg" << std::endl;
    else
        towerSprite.setTexture(towerTexture);
}

void Tower::upgrade()
{
    std::cout << "Tower upgraded" << std::endl;
}

void Tower::draw(sf::RenderWindow &window) { window.draw(towerSprite); }