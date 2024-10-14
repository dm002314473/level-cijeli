#include "Level.h"
#include "../commonFunction/CommonFunction.h"

void battleSetup(Troop *troop1, Troop *troop2);
void performBattle(Troop *troop1, Troop *troop2, float dtm);

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
    sf::Vector2f soldierSpawn1 = {1200, 370};
    createSoldier(*this, LVL1_SOLDIER_ATTACK1, soldierSpawn1);
    sf::Vector2f soldierSpawn2 = {1200, 770};
    createSoldier(*this, LVL1_SOLDIER_ATTACK1, soldierSpawn2);

    fillWaves();

    newWave = new sf::Sprite();
    sf::Texture *buttonTexture = getTexturePtr(getAllTexturesMatrix(), WAVE_SIGN, 0);
    spriteSetting(*newWave, *buttonTexture, 0.2);
    newWave->setPosition(10, 370);

    settingTowerStands();

    setMoney(1000);
    if (!font.loadFromFile("level-cijeli/Open_Sans/OpenSans-VariableFont_wdth,wght.ttf"))
        return;
    setTextBox(moneyText, font, moneyBox, 10, 10);
    ss << getMoney();
    moneyText.setString(ss.str());
    
    setTextBox(hearthText, font, hearthBox, 115, 10);
    ssh << hearth;
    hearthText.setString(ssh.str());
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
        sf::Time deltaTimeMove = globalClock.restart();
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


                    if(heroj[0]->getIsTroopSelected()){
                        heroj[0]->setTargetPosition(mousePosition);
                        heroj[0]->setIsTroopSelected(false);
                        heroj[0]->setShouldTroopMove(true);
                    }
                    if(heroj[0]->getSprite().getGlobalBounds().contains((sf::Vector2f)(mousePosition))){
                        heroj[0]->setIsTroopSelected(true);
                        heroj[0]->setShouldTroopMove(false);
                    }
                }
        }
        
        if(heroj[0]->getShouldTroopMove()){
            heroj[0]->performAnimation(heroj[0]->getWalkTexture(), sf::milliseconds(1000));
            heroj[0]->move(dtm);
            heroj[0]->setIsTroopFighting(false);
        }

        for (auto it = enemies.begin(); it != enemies.end();)
        {
            battleSetup(heroj[0], *it);
            performBattle(heroj[0], *it, dtm);

            for(auto &soldier : soldiers){
                battleSetup(soldier, *it);
                performBattle(soldier, *it, dtm);
            }

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
                int *stats = (*it)->getTroopSpecificStat();
                if((*it)->getIsTroopAlive())
                    updateHearth(stats[1]);
                else
                    updateMoney(-stats[0]);
                delete[] stats;
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

        for(auto &stand : towerStands)
            window->draw(*stand);

        for (auto &tower : towers)
            tower->draw(*window);

        for (auto &soldier : soldiers)
            soldier->draw(*window);

        for (auto &enemy : enemies)
            enemy->draw(*window);

        heroj[0]->draw(*window);

        window->draw(moneyBox);
        window->draw(moneyText);
        window->draw(hearthBox);
        window->draw(hearthText);

        if(showStartNewWaveFlag && wave <= 3)
            window->draw(*newWave);

        window->display();
    }
}


void Level::createHero(Level &level, int code, std::vector<int> heroStandPosition){
    Hero *hero = new Hero(level, code, heroStandPosition);
    heroj.push_back(hero);
}

void Level::createSoldier(Level &level, int code, sf::Vector2f spawnPosition){
    Soldier *vojnik = new Soldier(level, code, spawnPosition);
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

void Level::settingTowerStands()
{
    sf::Texture *towerStandTexture = getTexturePtr(getAllTexturesMatrix(), TOWER_STAND, 0);
    for (auto stand : towerStands)
        delete stand;
    towerStands.clear();

    for (size_t i = 0; i < towerStandsPositions.size(); i++)
    {
        sf::Sprite *stand = new sf::Sprite();
        spriteSetting(*stand, *towerStandTexture, 1.);
        stand->setOrigin(250, 250);

        int positionX = towerStandsPositions[i][0];
        int positionY = towerStandsPositions[i][1];
        stand->setPosition(positionX, positionY);

        towerStands.push_back(stand);
    }
}


void performBattle(Troop *troop1, Troop *troop2, float dtm) {
    if (troop1->getIsTroopFighting() && troop2->getIsTroopFighting() && troop1->getCurrentTarget() == troop2 && troop2->getCurrentTarget() == troop1) {
        
        troop1->setAttackCooldownTroop(troop1->getAttackCooldownTroop() + dtm);
        troop2->setAttackCooldownTroop(troop2->getAttackCooldownTroop() + dtm);

        if (troop1->getShouldTroopMove()) {
            troop1->setIsTroopFighting(false);
            troop1->setCurrentTarget(nullptr);
        }

        if (troop2->getShouldTroopMove()) {
            troop2->setIsTroopFighting(false);
            troop2->setCurrentTarget(nullptr);
        }

        if (troop1->getAttackCooldownTroop() >= troop1->getAttackSpeed() / 1000.0) {
            troop1->fightingTroop(troop2);
            troop2->updateHealthBar(troop2->getHealth());
            troop1->setAttackCooldownTroop(0.0);
        }

        if (troop2->getAttackCooldownTroop() >= troop2->getAttackSpeed() / 1000.0) {
            troop2->fightingTroop(troop1);
            troop1->updateHealthBar(troop1->getHealth());
            troop2->setAttackCooldownTroop(0.0);
        }

        if (troop1->getIsTroopFighting()) {
            troop1->performAnimation(troop1->getAttackTexture(), sf::milliseconds(troop1->getAttackSpeed()));
        }
        if (troop2->getIsTroopFighting()) {
            troop2->performAnimation(troop2->getAttackTexture(), sf::milliseconds(troop2->getAttackSpeed()));
        }

        if (!troop1->getIsTroopAlive()) {
            troop1->setIsTroopFighting(false);
            troop2->setIsTroopFighting(false);
            troop1->getSprite().setPosition(-1000, -1000); 
            troop2->move(dtm);
            troop2->setCurrentTarget(nullptr); 
        }

        if (!troop2->getIsTroopAlive()) {
            troop1->setIsTroopFighting(false);
            troop2->setIsTroopFighting(false);
            troop2->getSprite().setPosition(3000, 2000);
            troop1->setCurrentTarget(nullptr);
        }
    }
}


void battleSetup(Troop *troop1, Troop *troop2) {
    if (troop1->shouldTroopsInteract(troop2) && !troop1->getIsTroopFighting() && troop2->getCurrentTarget() == nullptr) {
        troop1->setIsTroopFighting(true);
        troop2->setIsTroopFighting(true);
        troop2->setCurrentTarget(troop1);
        troop1->setCurrentTarget(troop2);
    }

    if (troop1->getShouldTroopMove() || troop1->getIsTroopMoving()) {
        troop1->setIsTroopFighting(false);
        troop1->setCurrentTarget(nullptr);
        
        if (troop2->getCurrentTarget() == troop1) {
            troop2->setIsTroopFighting(false);
            troop2->setCurrentTarget(nullptr);
        }
    }
}

void Level::setMoney(int newMoney) { money = newMoney; }
int Level::getMoney() { return money; }

void Level::updateMoney(int price)
{
    setMoney(getMoney() - price);
    ss.str("");
    ss << getMoney();
    moneyText.setString(ss.str());
}

void Level::updateHearth(int lostHearth){
    hearth = hearth - lostHearth;
    ssh.str("");
    ssh << hearth;
    hearthText.setString(ssh.str());
}