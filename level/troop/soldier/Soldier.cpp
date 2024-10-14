#include "Soldier.h"
#include "../../Level.h"

Soldier::Soldier(Level &level, int code, sf::Vector2f spawnPosition) : Troop(level, code)
{
    setSoldierValues(level.getTroopStats(), code);
    getSprite().setPosition(spawnPosition);
    shouldHeroHeal = false;
}

void Soldier::setSoldierValues(std::vector<std::vector<int>> allStats, int code)
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

bool Soldier::soldierMoving(sf::Sprite &sprite, sf::Vector2i &mousePos)
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
bool Soldier::isEnemyInSoldiersRange(Troop *enemyTroop)
{
    if (isPointInCircle(enemyTroop->getSprite().getPosition(), getSprite().getPosition(), 150))
        return true;
    return false;
}

bool Soldier::isPointInCircle(sf::Vector2f point, sf::Vector2f circleCenter, float radius)
{
    float distance = std::sqrt(std::pow(point.x - circleCenter.x, 2) + std::pow(point.y - circleCenter.y, 2));
    return distance <= radius;
}

bool Soldier::isSoldierPositionIsOnPath(std::vector<sf::Color> colors, sf::Color pixelColor){
    for (int i = 0; i < colors.size(); i++)
        if(colors[i] == pixelColor)
            return true;
    return false;
}

bool Soldier::getShouldSoldierHeal() { return shouldHeroHeal; }
void Soldier::setShouldSoldierHeal(bool condition) { shouldHeroHeal = condition; }

int Soldier::getHealPerSecond() { return healPerSecond; }
void Soldier::setHealPerSecond(int newHealPerSecond) { healPerSecond = newHealPerSecond; }

void Soldier::soldierUpgrade(Level &level, int code){
    sf::Texture *texture = level.getTexturePtr(level.getAllTexturesMatrix(), code, 0);
    spriteSetting(getSprite(), *texture, .2);
    loadTroopTextures(level, code, getAttackTexture());
    loadTroopTextures(level, code + 1, getWalkTexture());
    setFullHealth(getHealth());
    getSprite().setPosition(500, 500);
    setValues(level.getTroopStats(), code);
    setSoldierValues(level.getTroopStats(), code);
    setFullHealth(getHealth());
}

int* Soldier::getTroopSpecificStat(){
    int* stats = new int[1];
    stats[0] = getHealPerSecond();
    return stats; 
}