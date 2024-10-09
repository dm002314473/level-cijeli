#pragma once

#include <iostream>
#include <SFML/Graphics.hpp>
#include "level-cijeli/troop/Troop.h"
#include "level-cijeli/troop/enemy/Enemy.h"

class Troop;
class Enemy;
class MainMenu;
class Level;

class Soldier : public Troop
{
private:
    bool shouldHeroHeal;
    int healPerSecond;
    sf::Vector2f soldierStandPosition;
public:
    Soldier(Level &level, int code) : Troop(level, code) {};

    void setValues(std::vector<std::vector<int>> allStats, int code);
    void setShouldSoldierHeal(bool condition);
    void setHealPerSecond(int newHealPerSecond);
    
    bool getShouldSoldierHeal();
    int getHealPerSecond();
    
    bool isSoldierPositionIsOnPath(std::vector<sf::Color> colors, sf::Color pixelColor);
    bool soldierMoving(sf::Sprite &sprite, sf::Vector2i &mousePos);
    bool isEnemyInSoldiersRange(Enemy *enemy);
    bool isPointInCircle(sf::Vector2f point, sf::Vector2f circleCenter, float radius);
    void fighting(Enemy *enemy);

    void soldierUpgrade(Level &level, int code);
};