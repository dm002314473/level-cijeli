#pragma once

#include <iostream>
#include <SFML/Graphics.hpp>
#include "level-cijeli/troop/Troop.h"
#include "level-cijeli/troop/hero/Hero.h"
#include "level-cijeli/troop/soldier/Soldier.h"

class Troop;
class Hero;
class Soldier;
class MainMenu;
class Level;

class Enemy : public Troop
{
private:
    std::vector<std::vector<int>> &waypoints;
    int currentWaypointIndex;
    bool outOfMap = false;     
    int bounty;
    int attackSpeed;
    int liveTaking;

public:
    Enemy(Level &level, int code, std::vector<std::vector<int>> &waypoints, int spawnDelayPixels) : Troop(level, code), waypoints(waypoints) {};

    void setValues(std::vector<std::vector<int>> allStats, int code);
    void setBounty(int newBounty);
    void setLiveTaking(int newLiveTaking);

    int getBounty();
    int getLiveTaking();

    bool shouldEnemyTurn();
    void move(float dtm);
    void stop();
    void stopMoving();
    void moveRight(float dtm); 
    void moveLeft(float dtm); 
    void moveUp(float dtm);
    void moveDown(float dtm);
    
    void fightingHero(Hero *hero);
    void fightingSoldier(Soldier *soldier);
};
