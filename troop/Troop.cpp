#include "Troop.h"

int generateRandomNumber(int min, int max);

Troop::Troop(Level &level, int code){
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
sf::Sprite Troop::getSprite() { return sprite; }
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


void Troop::performAnimation(std::vector<sf::Texture> &textures, sf::Time animationDuration)
{
    if (!isAnimating)
    {
        isAnimating = true;
        currentFrame = 0;
        animationClock.restart();
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

int generateRandomNumber(int min, int max) { return rand() % (max - min) + min; }