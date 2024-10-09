#pragma once

#include "Tower.h"

class ShootingTower : public Tower
{
private:
    sf::Time shotCooldown;
    sf::Time lastShotTime;

public:
    ShootingTower();
    void action(sf::Time currentTime) override;
    void shoot();
};