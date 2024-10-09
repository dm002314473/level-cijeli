#include "Hero.h"
#include "../../Level.h"

Hero::Hero(Level &level, int code, std::vector<int> heroStandPosition) : Troop(level, code)
{
    setHeroValues(level.getTroopStats(), code);
    getSprite().setPosition(heroStandPosition[0], heroStandPosition[1]);
    shouldHeroHeal = false;
}

void Hero::setHeroValues(std::vector<std::vector<int>> allStats, int code)
{
    for (int i = 0; i < allStats.size(); i++)
    {
        for (int j = 0; j < allStats[i].size(); j++)
        {
            if (allStats[i][0] == code)
                setHealPerSecond(allStats[i][9]);
        }
    }
}

bool Hero::heroMoving(sf::Sprite &sprite, sf::Vector2i &mousePos)
{
    int moveX = 0, moveY = 0;
    sf::Vector2f currentPos = sprite.getPosition();
    if (currentPos.x < mousePos.x)
        moveX = 1;
    else if (currentPos.x > mousePos.x)
        moveX = -1;

    if (currentPos.y < mousePos.y)
        moveY = 1;
    else if (currentPos.y > mousePos.y)
        moveY = -1;

    sprite.setPosition(currentPos.x + moveX, currentPos.y + moveY);

    if (int(currentPos.x) == mousePos.x && int(currentPos.y) == mousePos.y)
        return true;
    return false;
}
bool Hero::isEnemyInHeroesRange(Troop *enemyTroop)
{
    if (isPointInCircle(enemyTroop->getSprite().getPosition(), getSprite().getPosition(), 150))
        return true;
    return false;
}

bool Hero::isPointInCircle(sf::Vector2f point, sf::Vector2f circleCenter, float radius)
{
    float distance = std::sqrt(std::pow(point.x - circleCenter.x, 2) + std::pow(point.y - circleCenter.y, 2));
    return distance <= radius;
}

bool Hero::isHeroPositionIsOnPath(std::vector<sf::Color> colors, sf::Color pixelColor){
    for (int i = 0; i < colors.size(); i++)
        if(colors[i] == pixelColor)
            return true;
    return false;
}

bool Hero::getShouldHeroHeal() { return shouldHeroHeal; }
void Hero::setShouldHeroHeal(bool condition) { shouldHeroHeal = condition; }

int Hero::getHealPerSecond() { return healPerSecond; }
void Hero::setHealPerSecond(int newHealPerSecond) { healPerSecond = newHealPerSecond; }
