#include "ShootingTower.h"

ShootingTower::ShootingTower() : shotCooldown(sf::milliseconds(1000)), lastShotTime(sf::Time::Zero)
{
    std::cout << "ShootingTower created" << std::endl;
    loadImage();
}

void ShootingTower::action(sf::Time currentTime)
{
    if (currentTime - lastShotTime >= shotCooldown)
    {
        shoot();
        lastShotTime = currentTime;
    }
}

void ShootingTower::shoot()
{
    std::cout << "Shooting at enemies within range" << std::endl;
}