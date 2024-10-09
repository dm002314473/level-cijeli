#include "Hero.h"

Hero::Hero(Level &level, int code) : Troop(level, code)
{
    setValues(level.getTroopStats(), code);
    getSprite().setPosition(heroStandPosition);
    shouldHeroHeal = false;
}

void Hero::setValues(std::vector<std::vector<int>> allStats, int code)
{
    for (int i = 0; i < allStats.size(); i++)
    {
        for (int j = 0; j < allStats[i].size(); j++)
        {
            if (allStats[i][0] == code)
                setDamage(allStats[i][1], allStats[i][2]);
                setHealth(allStats[i][3]);
                setMagicArmor(allStats[i][4]);
                setPhysicalArmor(allStats[i][5]);
                setSpeedX(allStats[i][6]);
                setSpeedY(allStats[i][7]);
                setHealPerSecond(allStats[i][9]);
                setAttackSpeed(allStats[i][10]);
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
bool Hero::isEnemyInHeroesRange(Enemy *enemy)
{
    if (isPointInCircle(enemy->getSprite().getPosition(), getSprite().getPosition(), 150))
        return true;
    return false;
}

bool Hero::isPointInCircle(sf::Vector2f point, sf::Vector2f circleCenter, float radius)
{
    float distance = std::sqrt(std::pow(point.x - circleCenter.x, 2) + std::pow(point.y - circleCenter.y, 2));
    return distance <= radius;
}

void Hero::fighting(Enemy *enemy) { enemy->setHealth(enemy->getHealth() - getDamage()); }
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
