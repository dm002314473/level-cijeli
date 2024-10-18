#include "Level.h"
#include "../commonFunction/CommonFunction.h"

void battleSetup(Troop *friendlyTroop, Troop *enemyTroop);
void performBattle(Troop *friendlyTroop, Troop *enemyTroop, float dtm);
void addAnotherAttacker(Troop *friendlyTroop, Troop *enemyTroop, float dtm);


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
    

    fillWaves();

    newWave = new sf::Sprite();
    sf::Texture *buttonTexture = getTexturePtr(getAllTexturesMatrix(), WAVE_SIGN, 0);
    spriteSetting(*newWave, *buttonTexture, 0.2);
    newWave->setPosition(10, 370);

    moveFlag = new sf::Sprite();
    sf::Texture *newFlagTexture = getTexturePtr(getAllTexturesMatrix(), MOVEFLAG, 0);
    spriteSetting(*moveFlag, *newFlagTexture, 0.2);
    moveFlag->setPosition(100, 100);

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

    image = getTexturePtr(getAllTexturesMatrix(), GROUND_COLORS, 0)->copyToImage();
    imageSize = image.getSize();

    for (int y = 0; y < imageSize.y; ++y)
    {
        for (int x = 0; x < imageSize.x; ++x)
        {
            sf::Color pixelColor = image.getPixel(x, y);
            colors.push_back(pixelColor);
        }
    }
    
    image = backgroundTexture.copyToImage();
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

                    sf::Color pixelColor = image.getPixel(mousePosition.x, mousePosition.y);

                    if(!heroj[0]->getIsTroopMoving())
                        heroj[0]->checkTroopForMovement(heroj[0]->getSprite(), (sf::Vector2f)mousePosition, colors, pixelColor);
                    
                    for(auto &soldier : soldiers)
                        if(!soldier->getIsTroopMoving())
                            soldier->checkTroopForMovement(soldier->getSprite(), (sf::Vector2f)mousePosition, colors, pixelColor);

                }
        }
        
        if(heroj[0]->getShouldTroopMove()){
            heroj[0]->performAnimation(heroj[0]->getWalkTexture(), sf::milliseconds(1000));
            heroj[0]->move(dtm);
            heroj[0]->setIsTroopFighting(false);
        }
        for(auto &soldier : soldiers)
            if(soldier->getShouldTroopMove()){
                soldier->performAnimation(soldier->getWalkTexture(), sf::milliseconds(1000));
                soldier->move(dtm);
                soldier->setIsTroopFighting(false);
            }


        for (auto it = enemies.begin(); it != enemies.end();)
        {
            if((*it)->getAttackRange() > 70){
                (*it)->setIsTroopMoving(true);
                for(auto &soldier : soldiers)
                    if((*it)->shouldTroopsInteract(soldier)){
                        addAnotherAttacker(*it, soldier, dtm);
                        if(soldier->getIsTroopAlive())
                            (*it)->setIsTroopMoving(false);
                    }
                if((*it)->shouldTroopsInteract(heroj[0])){
                    addAnotherAttacker(*it, heroj[0], dtm);
                    if(heroj[0]->getIsTroopAlive())
                        (*it)->setIsTroopMoving(false);
                }
            }

            battleSetup(heroj[0], *it);
            performBattle(heroj[0], *it, dtm);

            
            for(auto &soldier : soldiers){
                battleSetup(soldier, *it);
                performBattle(soldier, *it, dtm);
            }

            //multiple attackers
            for(auto &soldier : soldiers)
                if(soldier->getCurrentTarget() == nullptr && soldier->shouldTroopsInteract(*it))
                    addAnotherAttacker(soldier, *it, dtm);

            if(heroj[0]->getCurrentTarget() == nullptr && heroj[0]->shouldTroopsInteract(*it))
                addAnotherAttacker(heroj[0], *it, dtm);

            if((*it)->getIsTroopMoving())
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
        window->draw(*moveFlag);

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
    sf::Vector2f position;
    position.x = spawnPosition.x - 75;
    position.y = spawnPosition.y - 43;
    Soldier *vojnik1 = new Soldier(level, code, position);
    soldiers.push_back(vojnik1);
    position.x = spawnPosition.x + 75;
    position.y = spawnPosition.y - 43;
    Soldier *vojnik2 = new Soldier(level, code, position);
    soldiers.push_back(vojnik2);
    position.x = spawnPosition.x;
    position.y = spawnPosition.y + 87;
    Soldier *vojnik3 = new Soldier(level, code, position);
    soldiers.push_back(vojnik3);
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
    // wave1.pushEnemyToWave(50100, 500);
    // wave1.pushEnemyToWave(50100, 1000);
    // wave1.pushEnemyToWave(50100, 1500);
    // wave1.pushEnemyToWave(50100, 2000);
    wave1.pushEnemyToWave(50300, 500);
    wave1.pushEnemyToWave(50300, 1500);
    wave1.pushEnemyToWave(50300, 2000);
    wave1.pushEnemyToWave(50300, 2500);
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

void performBattle(Troop *friendlyTroop, Troop *enemyTroop, float dtm) {
    if (friendlyTroop->getIsTroopFighting() && enemyTroop->getIsTroopFighting() && friendlyTroop->getCurrentTarget() == enemyTroop && enemyTroop->getCurrentTarget() == friendlyTroop) {
        
        friendlyTroop->setAttackCooldownTroop(friendlyTroop->getAttackCooldownTroop() + dtm);
        enemyTroop->setAttackCooldownTroop(enemyTroop->getAttackCooldownTroop() + dtm);

        if (friendlyTroop->getShouldTroopMove()) {
            friendlyTroop->setIsTroopFighting(false);
            friendlyTroop->setCurrentTarget(nullptr);
        }
        if (enemyTroop->getShouldTroopMove()) {
            enemyTroop->setIsTroopFighting(false);
            enemyTroop->setCurrentTarget(nullptr);
        }

        if (friendlyTroop->getAttackCooldownTroop() >= friendlyTroop->getAttackSpeed() / 1000.0) {
            friendlyTroop->fightingTroop(enemyTroop);
            enemyTroop->updateHealthBar(enemyTroop->getHealth());
            friendlyTroop->setAttackCooldownTroop(0.0);
        }
        if (enemyTroop->getAttackCooldownTroop() >= enemyTroop->getAttackSpeed() / 1000.0) {
            enemyTroop->fightingTroop(friendlyTroop);
            friendlyTroop->updateHealthBar(friendlyTroop->getHealth());
            enemyTroop->setAttackCooldownTroop(0.0);
        }

        if (friendlyTroop->getIsTroopFighting())
            friendlyTroop->performAnimation(friendlyTroop->getAttackTexture(), sf::milliseconds(friendlyTroop->getAttackSpeed()));
        if (enemyTroop->getIsTroopFighting())
            enemyTroop->performAnimation(enemyTroop->getAttackTexture(), sf::milliseconds(enemyTroop->getAttackSpeed()));

        if (!friendlyTroop->getIsTroopAlive()) {
            friendlyTroop->setIsTroopFighting(false);
            enemyTroop->setIsTroopFighting(false);
            friendlyTroop->getSprite().setPosition(-1000, -1000); 
            enemyTroop->move(dtm);
            enemyTroop->setCurrentTarget(nullptr);
            enemyTroop->setIsTroopMoving(true);
        }
        if (!enemyTroop->getIsTroopAlive()) {
            friendlyTroop->setIsTroopFighting(false);
            enemyTroop->setIsTroopFighting(false);
            enemyTroop->getSprite().setPosition(3000, 2000);
            friendlyTroop->setCurrentTarget(nullptr);
        }
    }
   
}


void battleSetup(Troop *friendlyTroop, Troop *enemyTroop) {
    if (friendlyTroop->shouldTroopsInteract(enemyTroop) && !friendlyTroop->getIsTroopFighting() && enemyTroop->getCurrentTarget() == nullptr) {
        friendlyTroop->setIsTroopFighting(true);
        friendlyTroop->setCurrentTarget(enemyTroop);
        enemyTroop->setIsTroopFighting(true);
        enemyTroop->setCurrentTarget(friendlyTroop);
        enemyTroop->setIsTroopMoving(false);
    }

    if (friendlyTroop->getShouldTroopMove() || friendlyTroop->getIsTroopMoving()) {
        friendlyTroop->setIsTroopFighting(false);
        friendlyTroop->setCurrentTarget(nullptr);
        
        if (enemyTroop->getCurrentTarget() == friendlyTroop) {
            enemyTroop->setIsTroopFighting(false);
            enemyTroop->setCurrentTarget(nullptr);
            enemyTroop->setIsTroopMoving(true);
        }
    }
}

void addAnotherAttacker(Troop *friendlyTroop, Troop *enemyTroop, float dtm){
    friendlyTroop->setAttackCooldownTroop(friendlyTroop->getAttackCooldownTroop() + dtm);
    
    friendlyTroop->performAnimation(friendlyTroop->getAttackTexture(), sf::milliseconds(friendlyTroop->getAttackSpeed()));

    if (friendlyTroop->getAttackCooldownTroop() >= friendlyTroop->getAttackSpeed() / 1000.0) {
            friendlyTroop->fightingTroop(enemyTroop);
            enemyTroop->updateHealthBar(enemyTroop->getHealth());
            friendlyTroop->setAttackCooldownTroop(0.0);
        }

    if (!enemyTroop->getIsTroopAlive()) {
        enemyTroop->setIsTroopFighting(false);
        enemyTroop->getSprite().setPosition(3000, 2000);
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