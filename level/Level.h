#pragma once

#include <iostream>
#include <SFML/Graphics.hpp>
#include <vector>
#include "towers/Tower.h"
#include "troop/Troop.h"
#include "troop/hero/Hero.h"
#include "troop/enemy/Enemy.h"
#include "troop/soldier/Soldier.h"
#include "waves/Wave.h"

struct Row
{
    int id;
    std::vector<sf::Texture> textures;
    std::vector<std::string> texturePaths;
};

class Level
{
private:
    std::vector<std::vector<int>> towerStats = {
        {60000, 70, 1, 3, 2000, 300, 110},
        {60001, 110, 3, 4, 2000, 300, 160},
        {60002, 160, 6, 10, 2000, 300, 230},
        {60003, 230, 12, 18, 2500, 300, 1000000},
        {60004, 230, 16, 24, 1500, 300, 1000000},
        {70000, 100, 9, 17, 1500, 350, 180},
        {70001, 180, 23, 43, 1500, 380, 240},
        {70002, 240, 40, 74, 1500, 400, 300},
        {70003, 300, 76, 140, 2000, 400, 1000000},
        {70004, 300, 42, 78, 1500, 410, 1000000},
        {80000, 70, 4, 6, 800, 350, 110},
        {80001, 110, 7, 11, 600, 390, 160},
        {80002, 160, 10, 16, 500, 410, 230},
        {80003, 230, 13, 19, 400, 410, 1000000},
        {80004, 230, 35, 65, 1500, 420, 1000000},
        {90000, 125, 8, 15, 3000, 300, 220},
        {90001, 220, 20, 40, 3000, 320, 320},
        {90002, 320, 30, 60, 3000, 350, 400},
        {90003, 400, 50, 100, 3500, 350, 1000000},
        {90004, 400, 60, 110, 2200, 370, 1000000}};
    std::vector<std::vector<int>> troopStats = {
        {50000, 20, 25, 700, 0, 1, 200, 200, 2, 50, 1500},
        {50100, 50, 70, 500, 0, 0, 400, 400, 1, 5, 1000},
        {50200, 5, 7, 500, 0, 0, 500, 500, 1, 5, 1000},
        {90015, 100, 200, 1045, 0, 1, 300, 300, 0, 50, 1000},
        {60100, 1, 3, 50, 0, 0, 300, 300, 10, 10, 1000},
        {60110, 3, 4, 100, 0, 1, 300, 300, 10, 15, 1360},
        {60120, 6, 10, 150, 0, 2, 300, 300, 10, 20, 1360},
        {60130, 16, 24, 250, 1, 1, 300, 300, 10, 40, 1370},
        {60140, 12, 18, 200, 1, 3, 300, 300, 14, 30, 1470}};
    std::vector<std::pair<int, std::vector<std::string>>> imagesPaths = {
        {1, {"level-cijeli/images/lvl1.png"}},
        {2, {"level-cijeli/images/lvl2.png"}},
        {3, {"level-cijeli/images/lvl3.png"}},
        {34, {"level-cijeli/images/restart.png"}},
        {35, {"level-cijeli/images/continue.png"}},
        {36, {"level-cijeli/images/exit.png"}},
        {37, {"level-cijeli/images/pause.png"}},
        {38, {"level-cijeli/images/forPause.png"}},
        {39, {"level-cijeli/images/redHealthBar.png"}},
        {40, {"level-cijeli/images/greenHealthBar.png"}},
        {4000, {"level-cijeli/images/bolt.png"}},
        {5000, {"level-cijeli/images/wave_sign.png"}},
        {9999, {"level-cijeli/images/main_map.png"}},
        {9998, {"level-cijeli/images/flag_for_lvl.png"}},
        {10000, {"level-cijeli/images/tower_stand.png"}},
        {10001, {"level-cijeli/images/tower_menu.png"}},
        {50000, {"level-cijeli/images/giant.png", "level-cijeli/images/giant_attack1.png", "level-cijeli/images/giant_attack2.png", "level-cijeli/images/giant_attack3.png", "level-cijeli/images/giant_attack4.png", "level-cijeli/images/giant_attack5.png"}},
        {50001, {"level-cijeli/images/giant_walk1.png", "level-cijeli/images/giant_walk2.png", "level-cijeli/images/giant_walk3.png"}},
        {50100, {"level-cijeli/images/goblin_attack1.png", "level-cijeli/images/goblin_attack2.png", "level-cijeli/images/goblin_attack3.png", "level-cijeli/images/goblin_attack4.png", "level-cijeli/images/goblin_attack5.png", "level-cijeli/images/goblin_attack6.png", "level-cijeli/images/goblin_attack7.png"}},
        {50101, {"level-cijeli/images/goblin_walk1.png", "level-cijeli/images/goblin_walk2.png", "level-cijeli/images/goblin_walk3.png", "level-cijeli/images/goblin_walk4.png"}},
        {50200, {"level-cijeli/images/gnome_attack1.png", "level-cijeli/images/gnome_attack2.png", "level-cijeli/images/gnome_attack3.png", "level-cijeli/images/gnome_attack4.png"}},
        {50201, {"level-cijeli/images/gnome_walk1.png", "level-cijeli/images/gnome_walk2.png", "level-cijeli/images/gnome_walk3.png"}},
        {69997, {"level-cijeli/images/abilityUpgradeMenu.png"}},
        {69998, {"level-cijeli/images/tower_upgrade_split.png"}},
        {69999, {"level-cijeli/images/tower_upgrade.png"}},
        {60000, {"level-cijeli/images/barracks_lvl1.png"}},
        {60001, {"level-cijeli/images/barracks_lvl2.png"}},
        {60002, {"level-cijeli/images/barracks_lvl3.png"}},
        {60003, {"level-cijeli/images/barracks_lvl4_v1.png"}},
        {60004, {"level-cijeli/images/barracks_lvl4_v2.png"}},
        {60100, {"level-cijeli/images/lvl1_soldier_attack1.png", "level-cijeli/images/lvl1_soldier_attack2.png", "level-cijeli/images/lvl1_soldier_attack3.png", "level-cijeli/images/lvl1_soldier_attack4.png", "level-cijeli/images/lvl1_soldier_attack5.png"}},
        {60101, {"level-cijeli/images/lvl1_soldier_walking1.png", "level-cijeli/images/lvl1_soldier_walking2.png", "level-cijeli/images/lvl1_soldier_walking3.png"}},
        {60110, {"level-cijeli/images/lvl2_soldier_attack1.png", "level-cijeli/images/lvl2_soldier_attack2.png", "level-cijeli/images/lvl2_soldier_attack3.png", "level-cijeli/images/lvl2_soldier_attack4.png", "level-cijeli/images/lvl2_soldier_attack5.png"}},
        {60111, {"level-cijeli/images/lvl2_soldier_walking1.png", "level-cijeli/images/lvl2_soldier_walking2.png", "level-cijeli/images/lvl2_soldier_walking3.png"}},
        {60120, {"level-cijeli/images/lvl3_soldier_attack1.png", "level-cijeli/images/lvl3_soldier_attack2.png", "level-cijeli/images/lvl3_soldier_attack3.png", "level-cijeli/images/lvl3_soldier_attack4.png", "level-cijeli/images/lvl3_soldier_attack5.png"}},
        {60121, {"level-cijeli/images/lvl3_soldier_walking1.png", "level-cijeli/images/lvl3_soldier_walking2.png", "level-cijeli/images/lvl3_soldier_walking3.png"}},
        {60130, {"level-cijeli/images/lvl4_v1_soldier_attack1.png", "level-cijeli/images/lvl4_v1_soldier_attack2.png", "level-cijeli/images/lvl4_v1_soldier_attack3.png", "level-cijeli/images/lvl4_v1_soldier_attack4.png", "level-cijeli/images/lvl4_v1_soldier_attack5.png"}},
        {60131, {"level-cijeli/images/lvl4_v1_soldier_walking1.png", "level-cijeli/images/lvl4_v1_soldier_walking2.png", "level-cijeli/images/lvl4_v1_soldier_walking3.png"}},
        {60140, {"level-cijeli/images/lvl4_v2_soldier_attack1.png", "level-cijeli/images/lvl4_v2_soldier_attack2.png", "level-cijeli/images/lvl4_v2_soldier_attack3.png", "level-cijeli/images/lvl4_v2_soldier_attack4.png", "level-cijeli/images/lvl4_v2_soldier_attack5.png"}},
        {60141, {"level-cijeli/images/lvl4_v2_soldier_walking1.png", "level-cijeli/images/lvl4_v2_soldier_walking2.png", "level-cijeli/images/lvl4_v2_soldier_walking3.png"}},
        {70000, {"level-cijeli/images/wiz_lvl1.png"}},
        {70001, {"level-cijeli/images/wiz_lvl2.png"}},
        {70002, {"level-cijeli/images/wiz_lvl3.png"}},
        {70003, {"level-cijeli/images/wiz_lvl4_v1.png"}},
        {70004, {"level-cijeli/images/wiz_lvl4_v2.png"}},
        {80000, {"level-cijeli/images/arc_lvl1.png"}},
        {80001, {"level-cijeli/images/arc_lvl2.png"}},
        {80002, {"level-cijeli/images/arc_lvl3.png"}},
        {80003, {"level-cijeli/images/arc_lvl4_v1.png"}},
        {80004, {"level-cijeli/images/arc_lvl4_v2.png"}},
        {90000, {"level-cijeli/images/bombard_lvl1.png"}},
        {90001, {"level-cijeli/images/bombard_lvl2.png"}},
        {90002, {"level-cijeli/images/bombard_lvl3.png"}},
        {90003, {"level-cijeli/images/bombard_lvl4_v1.png"}},
        {90004, {"level-cijeli/images/bombard_lvl4_v2.png"}},
        {90015, {"level-cijeli/images/hero1.png", "level-cijeli/images/hero1_attacking1.png", "level-cijeli/images/hero1_attacking2.png", "level-cijeli/images/hero1_attacking3.png", "level-cijeli/images/hero1_attacking4.png", "level-cijeli/images/hero1_attacking5.png"}},
        {90016, {"level-cijeli/images/hero1_walk1.png", "level-cijeli/images/hero1_walk2.png", "level-cijeli/images/hero1_walk3.png"}},
        {99999, {"level-cijeli/images/ground_colors.png"}}};
    std::vector<Row> allTexturesMatrix;
    sf::RenderWindow *window;
    sf::Texture backgroundTexture;
    sf::Sprite backgroundSprite;
    sf::Clock globalClock;
    sf::Clock moveClock;
    std::vector<Tower *> towers;
    std::vector<std::vector<int>> globalWaypoints  = {
        {0, 432, 2},
        {775, 550, 3},
        {775, 844, 2},
        {2200, 844, 0}};
    std::vector<std::vector<int>> towerStandsPositions = {
        {750, 465},
        {1500, 465},
        {690, 820},
        {1180, 780},
        {1180, 910},
        {1180, 1220}};
    std::vector<int> heroStandPosition = {1700, 350};
    
    std::vector<Wave> levelWaves;

    sf::Sprite *newWave;

    Troop *heroj;
    std::vector<Troop *> soldiers;
    std::vector<Troop *> enemies;

    int wave = 0;
    bool showStartNewWaveFlag = true;
    
    bool shouldHeroMove = false;

public:
    Level(sf::RenderWindow &window);

    std::vector<std::vector<int>> getTowerStats();
    std::vector<std::vector<int>> getTroopStats();
    std::vector<Row> &getAllTexturesMatrix();
    sf::Texture *getTexturePtr(std::vector<Row> &allTexturesMatrix, int code, int column);
    
    void loadBackground();
    void update();
    void createHero(Level &level, int code, std::vector<int> heroStandPosition);
    void createSoldier(Level &level, int code);

    void fillWaves();
    void startNewWave(int waveIndex);
};