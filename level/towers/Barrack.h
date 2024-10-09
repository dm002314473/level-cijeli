#pragma once

#include <SFML/Graphics.hpp>
#include <vector>
#include "Tower.h"

class Barrack : public Tower
{
private:
    sf::Time spawnCooldown;
    sf::Time lastSpawnTime;
    // std::vector<Troop *> soldiers;

public:
    Barrack();
    void action(sf::Time currentTime) override;
    void spawnSoldier();
    void draw(sf::RenderWindow &window);
};