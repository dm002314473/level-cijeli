#include "Level.h"

Level::Level(sf::RenderWindow &gameWindow) : window(&gameWindow)
{
    std::cout << "Level constructor called!" << std::endl;
    loadBackground();
}

void Level::loadBackground()
{
    if (!backgroundTexture.loadFromFile("level\\images\\background.jpeg"))
        std::cerr << "Failed to load background texture from background.png" << std::endl;
    else
        backgroundSprite.setTexture(backgroundTexture);
}

void Level::update()
{
    while (window->isOpen())
    {
        sf::Event event;
        while (window->pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window->close();
        }

        sf::Time elapsed = globalClock.restart();

        window->clear();
        window->draw(backgroundSprite);
        window->display();
    }
}