#include "Level.h"
#include "../commonFunction/CommonFunction.h"

Level::Level(sf::RenderWindow &gameWindow) : window(&gameWindow)
{
    std::cout << "Level constructor called!" << std::endl;
    loadBackground();

    for (auto& entry : imagesPaths) {
        int id = entry.first;
        std::vector<std::string> paths = entry.second;

        Row row;
        row.id = id;
        row.texturePaths = paths;

        for (std::string& path : paths) {
            sf::Texture texture;
            if (texture.loadFromFile(path)) {
                row.textures.push_back(texture);
            } else {
                std::cerr << "Error loading texture from path: " << path << std::endl;
            }
        }
        allTexturesMatrix.push_back(row);
    }

    createHero(*this, HERO1, heroStandPosition);
    createSoldier(*this, LVL1_SOLDIER_ATTACK1);
}

std::vector<std::vector<int>> Level::getTowerStats() { return towerStats; }
std::vector<std::vector<int>> Level::getTroopStats() { return troopStats; }
std::vector<Row> &Level::getAllTexturesMatrix() { return allTexturesMatrix; }
sf::Texture *Level::getTexturePtr(std::vector<Row> &allTexturesMatrix, int code, int column)
{
    for (auto &row : allTexturesMatrix)
    {
        if (row.id == code && column < row.textures.size())
            return &row.textures[column];
    }
    return nullptr;
}

void Level::loadBackground()
{
    if (!backgroundTexture.loadFromFile("level-cijeli/images/lvl3.png"))
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

        sf::Time currentTime = globalClock.getElapsedTime();
        globalClock.restart();

        for (auto &tower : towers)
            tower->action(currentTime);

        window->clear();
        window->draw(backgroundSprite);

        // draw towers
        for (auto &tower : towers)
            tower->draw(*window);

        heroj->draw(*window);
        vojnik->draw(*window);

        window->display();
    }
}


void Level::createHero(Level &level, int code, std::vector<int> heroStandPosition){
    heroj = new Hero(level, code, heroStandPosition);
}

void Level::createSoldier(Level &level, int code){
    vojnik = new Soldier(level, code);
}
