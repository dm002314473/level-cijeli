#pragma once

#include <iostream>
#include <SFML/Graphics.hpp>
#include "level-cijeli/troop/Troop.h"
#include "level-cijeli/troop/enemy/Enemy.h"

class Troop;
class Enemy;
class MainMenu;
class Level;

class Hero : public Troop
{
private:
    bool shouldHeroHeal;
    int healPerSecond;
    sf::Vector2f heroStandPosition;
public:
    Hero(Level &level, int code) : Troop(level, code) {};

    void setValues(std::vector<std::vector<int>> allStats, int code);
    void setShouldHeroHeal(bool condition);
    void setHealPerSecond(int newHealPerSecond);
    
    bool getShouldHeroHeal();
    int getHealPerSecond();
    
    bool isHeroPositionIsOnPath(std::vector<sf::Color> colors, sf::Color pixelColor);
    bool heroMoving(sf::Sprite &sprite, sf::Vector2i &mousePos);
    bool isEnemyInHeroesRange(Enemy *enemy);
    bool isPointInCircle(sf::Vector2f point, sf::Vector2f circleCenter, float radius);
    void fighting(Enemy *enemy);
};