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

    fillWaves();

    newWave = new sf::Sprite();
    sf::Texture *buttonTexture = getTexturePtr(getAllTexturesMatrix(), WAVE_SIGN, 0);
    spriteSetting(*newWave, *buttonTexture, 0.2);
    newWave->setPosition(10, 370);
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
        sf::Time deltaTimeMove = moveClock.restart();
        float dtm = deltaTimeMove.asSeconds();

        sf::Time currentTime = globalClock.getElapsedTime();
        globalClock.restart();
        
        sf::Event event;

        while (window->pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window->close();
            
            if (event.type == sf::Event::MouseButtonPressed)
                if (event.mouseButton.button == sf::Mouse::Left)
                {
                    sf::Vector2i mousePosition = sf::Mouse::getPosition(*window);

                    if (newWave->getGlobalBounds().contains((sf::Vector2f)(mousePosition)))
                    {
                        showStartNewWaveFlag = false;
                        startNewWave(wave);                  
                        wave++;
                    }

                }
        }
            
            //heroj->move(dtm);

        for (auto it = enemies.begin(); it != enemies.end();)
        {
            if (!(*it)->getIsTroopFighting())
            {
                (*it)->move(dtm);
                (*it)->performAnimation((*it)->getWalkTexture(), sf::milliseconds(1000));
            }

            if ((*it)->getSprite().getPosition().x < 0)
                showStartNewWaveFlag = false;
            else
                showStartNewWaveFlag = true;

           if ((*it)->isOutOfMap())
           {
               delete *it;
               it = enemies.erase(it);
           }
           else
               ++it;
        }

        for (auto &tower : towers)
            tower->action(currentTime);

        window->clear();
        window->draw(backgroundSprite);

        for (auto &tower : towers)
            tower->draw(*window);

        for (auto &soldier : soldiers)
            soldier->draw(*window);

        for (auto &enemy : enemies)
            enemy->draw(*window);

        heroj->draw(*window);

        if(showStartNewWaveFlag && wave <= 3)
            window->draw(*newWave);

        window->display();
    }
}


void Level::createHero(Level &level, int code, std::vector<int> heroStandPosition){
    heroj = new Hero(level, code, heroStandPosition);
}

void Level::createSoldier(Level &level, int code){
    Soldier *vojnik = new Soldier(level, code);
    soldiers.push_back(vojnik);
}

void Level::startNewWave(int waveIndex)
{
    levelWaves[waveIndex];
    for (int i = 0; i < levelWaves[waveIndex].getSize(); i++)
    {
        Enemy *enemy = new Enemy(*this, levelWaves[waveIndex].getTroop(i).first, globalWaypoints , levelWaves[waveIndex].getTroop(i).second);
        enemies.push_back(enemy);
    }
}

void Level::fillWaves(){
    Wave wave1;
    wave1.pushEnemyToWave(50100, 500);
    wave1.pushEnemyToWave(50100, 1000);
    wave1.pushEnemyToWave(50100, 1500);
    wave1.pushEnemyToWave(50100, 2000);
    levelWaves.push_back(wave1);

    Wave wave2;
    wave2.pushEnemyToWave(50100, 500);
    wave2.pushEnemyToWave(50100, 1000);
    wave2.pushEnemyToWave(50100, 1500);
    wave2.pushEnemyToWave(50100, 2000);
    wave2.pushEnemyToWave(50000, 3000);
    levelWaves.push_back(wave2);
   
    Wave wave3;
    wave3.pushEnemyToWave(50100, 500);
    wave3.pushEnemyToWave(50100, 500);
    wave3.pushEnemyToWave(50100, 1000);
    wave3.pushEnemyToWave(50100, 1000);
    wave3.pushEnemyToWave(50100, 1500);
    wave3.pushEnemyToWave(50100, 1500);
    wave3.pushEnemyToWave(50100, 2000);
    wave3.pushEnemyToWave(50100, 2000);
    wave3.pushEnemyToWave(50000, 3000);
    wave3.pushEnemyToWave(50000, 3000);
    levelWaves.push_back(wave3);

    Wave wave4;
    wave4.pushEnemyToWave(50100, 500);
    wave4.pushEnemyToWave(50100, 500);
    wave4.pushEnemyToWave(50100, 1000);
    wave4.pushEnemyToWave(50100, 1000);
    wave4.pushEnemyToWave(50100, 1500);
    wave4.pushEnemyToWave(50100, 1500);
    wave4.pushEnemyToWave(50100, 2000);
    wave4.pushEnemyToWave(50100, 2000);
    wave4.pushEnemyToWave(50000, 3000);
    wave4.pushEnemyToWave(50000, 3000);
    wave4.pushEnemyToWave(50200, 4000);
    levelWaves.push_back(wave4);
}
