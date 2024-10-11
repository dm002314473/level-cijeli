#pragma once

#include <iostream>
#include <cmath>
#include <SFML/Graphics.hpp>
#include "../Troop.h"
#include "../../../commonFunction/CommonFunction.h"

class Level;

class Hero : public Troop
{
private:
    bool shouldHeroHeal;
    int healPerSecond;
    sf::Vector2f heroStandPosition;
    sf::Vector2f targetPosition;
public:
    Hero(Level &level, int code, std::vector<int> heroStandPosition);

    void setHeroValues(std::vector<std::vector<int>> allStats, int code);
    void setShouldHeroHeal(bool condition);
    void setHealPerSecond(int newHealPerSecond);
    
    bool getShouldHeroHeal();
    int getHealPerSecond();
    
    bool isHeroPositionIsOnPath(std::vector<sf::Color> colors, sf::Color pixelColor);
    bool isEnemyInHeroesRange(Troop *enemyTroop);
    bool isPointInCircle(sf::Vector2f point, sf::Vector2f circleCenter, float radius);

    void setTargetPosition(sf::Vector2i &mousePos);
    void move(float dtm) override;
    bool isOutOfMap() override { return false; }
};