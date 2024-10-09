#pragma once

#include <iostream>
#include <SFML/Graphics.hpp>
#include "level-cijeli/level/Level.h"
#include "level-cijeli/commonFunction/CommonFunction.h"

class Level;
class MainMenu;

class Troop
{
private:
    sf::Sprite sprite;
    sf::Sprite redHealthBarSprite;
    sf::Sprite greenHealthBarSprite;
    std::vector<sf::Texture> attackTextures;
    std::vector<sf::Texture> walkTextures;
    sf::Clock animationClock;
    int currentFrame = 0;
    bool isAnimating = false;
    sf::Time frameDuration = sf::milliseconds(1000 / 6.);
    sf::Time animationDuration = sf::milliseconds(1000);
    int speedX;
    int speedY;
    int damage[2];
    int health;
    int magicArmor;
    int physicalArmor;
    int attackSpeed;
    bool isTroopFighting = false;
    bool isTroopAlive = true;
    int fullHealth;
public:
    Troop(Level &level, int code);

    void setHealth(int newHealth);
    void setDamage(int newDamage1, int newDamage2);
    void setSpeedX(int newSpeedX);
    void setSpeedY(int newSpeedY);
    void setMagicArmor(int newMagicArmor);
    void setPhysicalArmor(int newPhysicalArmor);
    void setAttackSpeed(int newAttackSpeed);
    void setSprite(sf::Sprite newSprite);
    void setIsTroopFighting(bool condition);
    void setIsTroopAlive(bool condition);
    void setFullHealth(int newFullHealth);

    int getHealth();
    int getDamage();
    int getSpeedX();
    int getSpeedY();
    int getMagicArmor();
    int getPhysicalArmor();
    int getAttackSpeed();
    sf::Sprite getSprite();
    bool getIsTroopFighting();
    bool getIsTroopAlive();
    int getFullHealth();
    std::vector<sf::Texture>& getWalkTexture();
    std::vector<sf::Texture>& getAttackTexture();

    void loadTroopTextures(Level &level, int code, std::vector<sf::Texture> &textures);

    void performAnimation(std::vector<sf::Texture> &textures, sf::Time animationDuration);

    void draw(sf::RenderWindow &window);
    void updateHealthBarsPosition();
    void updateHealthBar(int currentHealth);
};