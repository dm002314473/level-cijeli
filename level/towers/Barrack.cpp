#include <iostream>
#include "Barrack.h"

Barrack::Barrack() : spawnCooldown(sf::milliseconds(5000)), lastSpawnTime(sf::Time::Zero)
{
    std::cout << "Barrack created" << std::endl;
    loadImage();
}

// ovo je tip barake koja bi spawnala enemije
// triba prilagodit da bude friendly baraka
void Barrack::action(sf::Time currentTime)
{
    if (currentTime - lastSpawnTime >= spawnCooldown)
    {
        spawnSoldier();
        lastSpawnTime = currentTime;
    }
}

void Barrack::spawnSoldier()
{
    std::cout << "Spawning a soldier" << std::endl;

    // Troop soldier = new Troop();
    // soldiers.push_back(soldier);
}

void Barrack::draw(sf::RenderWindow &window)
{
    window.draw(towerSprite);
    // for (auto &soldier : soldiers)
    //     soldier.draw(window);
}