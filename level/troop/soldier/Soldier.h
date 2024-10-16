#pragma once

#include <iostream>
#include <cmath>
#include <SFML/Graphics.hpp>
#include "../Troop.h"
#include "../../../commonFunction/CommonFunction.h"

class Level;

class Soldier : public Troop
{
private:
    bool shouldHeroHeal;
    int healPerSecond;
    sf::Vector2f soldierStandPosition;
    sf::Vector2f targetPosition;
public:
    Soldier(Level &level, int code, sf::Vector2f spawnPosition);

    void setSoldierValues(std::vector<std::vector<int>> allStats, int code);
    void setShouldSoldierHeal(bool condition);
    void setHealPerSecond(int newHealPerSecond);
    
    bool getShouldSoldierHeal();
    int getHealPerSecond();
    
    bool isSoldierPositionIsOnPath(std::vector<sf::Color> colors, sf::Color pixelColor);
    bool isEnemyInSoldiersRange(Troop *enemyTroop);
    bool isPointInCircle(sf::Vector2f point, sf::Vector2f circleCenter, float radius);

    void soldierUpgrade(Level &level, int code);

    void setTargetPosition(sf::Vector2i mousePos) override;
    void move(float dtm) override;
    bool isOutOfMap() override { return false; }

    int *getTroopSpecificStat();
};