#pragma once


#include <iostream>
#include <SFML/Graphics.hpp>
#include <vector>

class Wave
{
private:
    std::vector<std::pair<int, int>> wave;

public:
    Wave();
    void pushEnemyToWave(int nameCode, int spawnTime);
    int getSize();
    std::pair<int, int> getTroop(int index);
    void erase();
};