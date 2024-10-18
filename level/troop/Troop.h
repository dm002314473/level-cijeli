#pragma once

#include <iostream>
#include <SFML/Graphics.hpp>
#include "../../commonFunction/CommonFunction.h"

class Level;

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
    int attackRange;
    bool isTroopFighting = false;
    bool isTroopAlive = true;
    int fullHealth;

    bool isTroopSelected = false;
    bool shouldTroopMove = false;
    bool isTroopMoving = false;

    float attackCooldownTroop = 0.0;

    Troop *currentTarget = nullptr;

public:
    Troop(Level &level, int code);

    void setValues(std::vector<std::vector<int>> allStats, int code);
    void setHealth(int newHealth);
    void setDamage(int newDamage1, int newDamage2);
    void setSpeedX(int newSpeedX);
    void setSpeedY(int newSpeedY);
    void setMagicArmor(int newMagicArmor);
    void setPhysicalArmor(int newPhysicalArmor);
    void setAttackSpeed(int newAttackSpeed);
    void setAttackRange(int newAttackRAnge);
    void setSprite(sf::Sprite newSprite);
    void setIsTroopFighting(bool condition);
    void setIsTroopAlive(bool condition);
    void setFullHealth(int newFullHealth);
    void setIsTroopSelected(bool condition);
    void setShouldTroopMove(bool condition);
    void setAttackCooldownTroop(float newAttackCooldownTroop);
    void setIsTroopMoving(bool condition);
    void setCurrentTarget(Troop *newCurrentTarget);

    int getHealth();
    int getDamage();
    int getSpeedX();
    int getSpeedY();
    int getMagicArmor();
    int getPhysicalArmor();
    int getAttackSpeed();
    int getAttackRange();
    sf::Sprite& getSprite();
    bool getIsTroopFighting();
    bool getIsTroopAlive();
    int getFullHealth();
    std::vector<sf::Texture>& getWalkTexture();
    std::vector<sf::Texture>& getAttackTexture();
    bool getIsTroopSelected();
    bool getShouldTroopMove();
    float getAttackCooldownTroop();
    bool getIsTroopMoving();
    Troop* getCurrentTarget();

    void loadTroopTextures(Level &level, int code, std::vector<sf::Texture> &textures);

    void performAnimation(std::vector<sf::Texture> &textures, sf::Time animationDuration);
    void idleAnimation(std::vector<sf::Texture> &textures);

    void draw(sf::RenderWindow &window);
    void updateHealthBarsPosition();
    void updateHealthBar(int currentHealth);

    
    void fightingTroop(Troop *troop);
    
    virtual void move(float dtm) = 0;
    virtual bool isOutOfMap() = 0;
    virtual void setTargetPosition(sf::Vector2i mousePos) = 0;
    virtual int* getTroopSpecificStat() = 0;

    bool isTroopClicked(sf::Vector2i &mousePos);

    void stopMoving();
    void moveRight(float dtm); 
    void moveLeft(float dtm); 
    void moveUp(float dtm);
    void moveDown(float dtm);

    bool shouldTroopsInteract(Troop *troop1);

    bool isTroopOnPath(std::vector<sf::Color> colors, sf::Color pixelColor);
    void checkTroopForMovement(sf::Sprite spriteForMove, sf::Vector2f mousePosition, std::vector<sf::Color> colors, sf::Color pixelColor);
};