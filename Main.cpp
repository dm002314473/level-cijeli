#include <iostream>
#include "level/Level.h"

int main()
{
    sf::RenderWindow window(sf::VideoMode(1920, 1080), "Cijeli level");

    Level level(window);
    level.update();

    return 0;
}