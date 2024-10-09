#pragma once

#include <iostream>
#include <SFML/Graphics.hpp>

struct Row
{
    int id;
    std::vector<sf::Texture> textures;
    std::vector<std::string> texturePaths;
};

class Level
{
private:
    std::vector<std::vector<int>> towerStats;
    std::vector<std::vector<int>> troopStats;
    std::vector<std::pair<int, std::vector<std::string>>> imagesPaths;
    std::vector<Row> allTexturesMatrix;
public:
    Level();
    
    std::vector<std::vector<int>> getTowerStats();
    std::vector<std::vector<int>> getTroopStats();
    std::vector<Row> &getAllTexturesMatrix() { return allTexturesMatrix; }
    sf::Texture *getTexturePtr(std::vector<Row> &allTexturesMatrix, int code, int column);
};