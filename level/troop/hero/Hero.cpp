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

void Hero::move(float dtm)
{
    sf::Vector2f targetPos((float)(targetPosition.x), (float)(targetPosition.y));
    sf::Vector2f currentPos = getSprite().getPosition();
    float tolerance = 0.1f;

    if (std::abs(currentPos.x - targetPos.x) < tolerance && std::abs(currentPos.y - targetPos.y) < tolerance)
    {
        stopMoving();
        setShouldTroopMove(false);
        idleAnimation(getWalkTexture());
        return;
    }

    setIsTroopMoving(true);

    if (currentPos.x < targetPos.x)
        moveRight(dtm); 
    else if (currentPos.x > targetPos.x)
        moveLeft(dtm);

    if (currentPos.y < targetPos.y)
        moveDown(dtm);
    else if (currentPos.y > targetPos.y)
        moveUp(dtm);

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

void Hero::setTargetPosition(sf::Vector2i &mousePos) { targetPosition = static_cast<sf::Vector2f>(mousePos); }

int* Hero::getTroopSpecificStat(){
    int* stats = new int[1];
    stats[0] = getHealPerSecond();
    return stats;
}