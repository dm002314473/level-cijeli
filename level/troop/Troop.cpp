#include "Troop.h"
#include "../Level.h"

int generateRandomNumber(int min, int max);

Troop::Troop(Level &level, int code){
    setValues(level.getTroopStats(), code);
    sf::Texture *texture = level.getTexturePtr(level.getAllTexturesMatrix(), code, 0);
    spriteSetting(sprite, *texture, .2);
    sprite.setOrigin(150, 150);
    loadTroopTextures(level, code, attackTextures);
    loadTroopTextures(level, code + 1, walkTextures);
    sf::Texture *redBarTexture = level.getTexturePtr(level.getAllTexturesMatrix(), REDHEALTHBAR, 0);
    spriteSetting(redHealthBarSprite, *redBarTexture, .2);
    sf::Texture *greenBarTexture = level.getTexturePtr(level.getAllTexturesMatrix(), GREENHEALTHBAR, 0);
    spriteSetting(greenHealthBarSprite, *greenBarTexture, .2);
    redHealthBarSprite.setOrigin(50, 10);
    redHealthBarSprite.setPosition(sprite.getPosition().x, sprite.getPosition().y - 10);
    greenHealthBarSprite.setPosition(redHealthBarSprite.getPosition());
    fullHealth = health;
}

void Troop::setValues(std::vector<std::vector<int>> allStats, int code)
{
    for (int i = 0; i < allStats.size(); i++)
    {
        for (int j = 0; j < allStats[i].size(); j++)
        {
            if (allStats[i][0] == code){
                setDamage(allStats[i][1], allStats[i][2]);
                setHealth(allStats[i][3]);
                setMagicArmor(allStats[i][4]);
                setPhysicalArmor(allStats[i][5]);
                setSpeedX(allStats[i][6]);
                setSpeedY(allStats[i][7]);
                setAttackSpeed(allStats[i][10]);
            }
        }
    }
}

void Troop::setHealth(int newHealth) { health = newHealth; }
void Troop::setDamage(int newDamage1, int newDamage2)
{
    damage[0] = newDamage1;
    damage[1] = newDamage2;
}
void Troop::setSpeedX(int newSpeedX) { speedX = newSpeedX; }
void Troop::setSpeedY(int newSpeedY) { speedY = newSpeedY; }
void Troop::setMagicArmor(int newMagicArmor) { magicArmor = newMagicArmor; }
void Troop::setPhysicalArmor(int newPhysicalArmor) { physicalArmor = newPhysicalArmor; }
void Troop::setAttackSpeed(int newAttackSpeed) { attackSpeed = newAttackSpeed; }
void Troop::setSprite(sf::Sprite newSprite) { sprite = newSprite; }
void Troop::setIsTroopFighting(bool condition) { isTroopFighting = condition; }
void Troop::setIsTroopAlive(bool condition) { isTroopAlive = condition; }
void Troop::setFullHealth(int newFullHealth) { fullHealth = newFullHealth; }

int Troop::getHealth() { return health; }
int Troop::getDamage() { return generateRandomNumber(damage[0], damage[1]); }
int Troop::getSpeedX() { return speedX; }
int Troop::getSpeedY() { return speedY; }
int Troop::getMagicArmor() { return magicArmor; }
int Troop::getPhysicalArmor() { return physicalArmor; }
int Troop::getAttackSpeed() { return attackSpeed; }
sf::Sprite& Troop::getSprite() { return sprite; }
bool Troop::getIsTroopFighting() { return isTroopFighting; }
bool Troop::getIsTroopAlive()
{
    if (health > 0)
        return true;
    else
        return false;
}
std::vector<sf::Texture>& Troop::getAttackTexture() { return attackTextures; }
std::vector<sf::Texture>& Troop::getWalkTexture() { return walkTextures; }
int Troop::getFullHealth() { return fullHealth; }

void Troop::loadTroopTextures(Level &level, int code, std::vector<sf::Texture> &textures)
{
    bool rowFound = false;
    for (auto &row : level.getAllTexturesMatrix())
    {
        if (row.id == code)
        {
            rowFound = true;
            for (size_t i = 0; i < row.textures.size(); ++i)
            {
                sf::Texture texture;
                if (texture.loadFromFile(row.texturePaths[i]))
                    textures.push_back(texture);
                else
                    std::cerr << "Failed to load texture from path: " << row.texturePaths[i] << std::endl;
            }
            break;
        }
    }

    if (!rowFound)
    {
        std::cerr << "No textures found for the code: " << code << std::endl;
    }
}

void Troop::idleAnimation(std::vector<sf::Texture> &textures) { sprite.setTexture(textures[0]); }

void Troop::performAnimation(std::vector<sf::Texture> &textures, sf::Time animationDuration)
{
    if (!isAnimating) 
    {
        isAnimating = true;
        currentFrame = 0;
        animationClock.restart();
        
        frameDuration = animationDuration / (float)textures.size();
    }

    if (isAnimating)
    {
        sf::Time elapsedTime = animationClock.getElapsedTime();
        if (elapsedTime >= frameDuration)
        {
            currentFrame++;
            if (currentFrame >= textures.size() || elapsedTime >= animationDuration)
            {
                isAnimating = false;
                currentFrame = 0;
                sprite.setTexture(textures[0]); 
                return;
            }
            sprite.setTexture(textures[currentFrame]);
            animationClock.restart();
        }
    }
}

void Troop::draw(sf::RenderWindow &window) {
    updateHealthBarsPosition();
    window.draw(sprite);
    window.draw(redHealthBarSprite);
    window.draw(greenHealthBarSprite);
}

void Troop::updateHealthBarsPosition() {
    redHealthBarSprite.setPosition(sprite.getPosition().x - 40, sprite.getPosition().y  - 70);
    greenHealthBarSprite.setPosition(redHealthBarSprite.getPosition().x -10, redHealthBarSprite.getPosition().y - 2);
}

void Troop::updateHealthBar(int currentHealth){
    greenHealthBarSprite.setScale(.2 - .2 * (1 - currentHealth * 1. / fullHealth), .2);
}


void Troop::fightingTroop(Troop *troop) { 
    troop->setHealth(troop->getHealth() - getDamage());
    if(troop->getHealth() < 0)
        troop->setIsTroopAlive(false);
}

int generateRandomNumber(int min, int max) { return rand() % (max - min) + min; }


void Troop::stopMoving() { 
    sprite.setPosition(sprite.getPosition().x, sprite.getPosition().y); 
    setIsTroopMoving(false);
}
void Troop::moveRight(float dtm) { sprite.setPosition(sprite.getPosition().x + getSpeedX() * dtm, sprite.getPosition().y); }
void Troop::moveLeft(float dtm) { sprite.setPosition(sprite.getPosition().x - getSpeedX() * dtm, sprite.getPosition().y); }
void Troop::moveUp(float dtm) { sprite.setPosition(sprite.getPosition().x, sprite.getPosition().y - getSpeedY() * dtm); }
void Troop::moveDown(float dtm) { sprite.setPosition(sprite.getPosition().x, sprite.getPosition().y + getSpeedY() * dtm); }

bool Troop::isTroopClicked(sf::Vector2i &mousePos){
    if(sprite.getGlobalBounds().contains((sf::Vector2f(mousePos))))
        return true;
    return false;
}

bool Troop::getIsTroopSelected() { return isTroopSelected; }
void Troop::setIsTroopSelected(bool condition) { isTroopSelected = condition; }


bool Troop::getShouldTroopMove() { return shouldTroopMove; }
void Troop::setShouldTroopMove(bool condition) { shouldTroopMove = condition; }



bool Troop::shouldTroopsInteract(Troop *troop1){
    float distance = std::sqrt(std::pow(troop1->sprite.getPosition().x - sprite.getPosition().x, 2) + std::pow(troop1->sprite.getPosition().y - sprite.getPosition().y, 2));
    int radius = 70;
    if(distance <= radius)
        return true;
    return false;
}

void Troop::setAttackCooldownTroop(float newAttackCooldownTroop) { attackCooldownTroop = newAttackCooldownTroop; }
float Troop::getAttackCooldownTroop() { return attackCooldownTroop; }

void Troop::setIsTroopMoving(bool newIsTroopMoving) { isTroopMoving = newIsTroopMoving; }
bool Troop::getIsTroopMoving() { return isTroopMoving; }

void Troop::setCurrentTarget(Troop *newCurrentTarget) { currentTarget = newCurrentTarget; }
Troop* Troop::getCurrentTarget() { return currentTarget; }