#include "Level.h"

Level::Level() { 
    std::cout << "Level constructor called!" << std::endl;
    towerStats = {
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
    troopStats = {
        {50000, 20, 25, 700, 0, 1, 200, 200, 2, 50, 1500},
        {50100, 50, 70, 500, 0, 0, 400, 400, 1, 5, 1000},
        {50200, 5, 7, 500, 0, 0, 500, 500, 1, 5, 1000},
        {90015, 100, 200, 1045, 0, 1, 300, 300, 0, 50, 1000},
        {60100, 1, 3, 50, 0, 0, 300, 300, 10, 10, 1000},
        {60110, 3, 4, 100, 0, 1, 300, 300, 10, 15, 1360},
        {60120, 6, 10, 150, 0, 2, 300, 300, 10, 20, 1360},
        {60130, 16, 24, 250, 1, 1, 300, 300, 10, 40, 1370},
        {60140, 12, 18, 200, 1, 3, 300, 300, 14, 30, 1470}};

    imagesPaths = {
        {1, {"GeneralRehearsal/images/lvl1.png"}},
        {2, {"GeneralRehearsal/images/lvl2.png"}},
        {3, {"GeneralRehearsal/images/lvl3.png"}},
        {34, {"GeneralRehearsal/images/restart.png"}},
        {35, {"GeneralRehearsal/images/continue.png"}},
        {36, {"GeneralRehearsal/images/exit.png"}},
        {37, {"GeneralRehearsal/images/pause.png"}},
        {38, {"GeneralRehearsal/images/forPause.png"}},
        {39, {"GeneralRehearsal/images/redHealthBar.png"}},
        {40, {"GeneralRehearsal/images/greenHealthBar.png"}},
        {4000, {"GeneralRehearsal/images/bolt.png"}},
        {5000, {"GeneralRehearsal/images/wave_sign.png"}},
        {9999, {"GeneralRehearsal/images/main_map.png"}},
        {9998, {"GeneralRehearsal/images/flag_for_lvl.png"}},
        {10000, {"GeneralRehearsal/images/tower_stand.png"}},
        {10001, {"GeneralRehearsal/images/tower_menu.png"}},
        {50000, {"GeneralRehearsal/images/giant.png", "GeneralRehearsal/images/giant_attack1.png", "GeneralRehearsal/images/giant_attack2.png", "GeneralRehearsal/images/giant_attack3.png", "GeneralRehearsal/images/giant_attack4.png", "GeneralRehearsal/images/giant_attack5.png"}},
        {50001, {"GeneralRehearsal/images/giant_walk1.png", "GeneralRehearsal/images/giant_walk2.png", "GeneralRehearsal/images/giant_walk3.png"}},
        {50100, {"GeneralRehearsal/images/goblin_attack1.png", "GeneralRehearsal/images/goblin_attack2.png", "GeneralRehearsal/images/goblin_attack3.png", "GeneralRehearsal/images/goblin_attack4.png", "GeneralRehearsal/images/goblin_attack5.png", "GeneralRehearsal/images/goblin_attack6.png", "GeneralRehearsal/images/goblin_attack7.png"}},
        {50101, {"GeneralRehearsal/images/goblin_walk1.png", "GeneralRehearsal/images/goblin_walk2.png", "GeneralRehearsal/images/goblin_walk3.png", "GeneralRehearsal/images/goblin_walk4.png"}},
        {50200, {"GeneralRehearsal/images/gnome_attack1.png", "GeneralRehearsal/images/gnome_attack2.png", "GeneralRehearsal/images/gnome_attack3.png", "GeneralRehearsal/images/gnome_attack4.png"}},
        {50201, {"GeneralRehearsal/images/gnome_walk1.png", "GeneralRehearsal/images/gnome_walk2.png", "GeneralRehearsal/images/gnome_walk3.png"}},
        {69997, {"GeneralRehearsal/images/abilityUpgradeMenu.png"}},
        {69998, {"GeneralRehearsal/images/tower_upgrade_split.png"}},
        {69999, {"GeneralRehearsal/images/tower_upgrade.png"}},
        {60000, {"GeneralRehearsal/images/barracks_lvl1.png"}},
        {60001, {"GeneralRehearsal/images/barracks_lvl2.png"}},
        {60002, {"GeneralRehearsal/images/barracks_lvl3.png"}},
        {60003, {"GeneralRehearsal/images/barracks_lvl4_v1.png"}},
        {60004, {"GeneralRehearsal/images/barracks_lvl4_v2.png"}},
        {60100, {"GeneralRehearsal/images/lvl1_soldier_attack1.png", "GeneralRehearsal/images/lvl1_soldier_attack2.png", "GeneralRehearsal/images/lvl1_soldier_attack3.png", "GeneralRehearsal/images/lvl1_soldier_attack4.png", "GeneralRehearsal/images/lvl1_soldier_attack5.png"}},
        {60101, {"GeneralRehearsal/images/lvl1_soldier_walking1.png", "GeneralRehearsal/images/lvl1_soldier_walking2.png", "GeneralRehearsal/images/lvl1_soldier_walking3.png"}},
        {60110, {"GeneralRehearsal/images/lvl2_soldier_attack1.png", "GeneralRehearsal/images/lvl2_soldier_attack2.png", "GeneralRehearsal/images/lvl2_soldier_attack3.png", "GeneralRehearsal/images/lvl2_soldier_attack4.png", "GeneralRehearsal/images/lvl2_soldier_attack5.png"}},
        {60111, {"GeneralRehearsal/images/lvl2_soldier_walking1.png", "GeneralRehearsal/images/lvl2_soldier_walking2.png", "GeneralRehearsal/images/lvl2_soldier_walking3.png"}},
        {60120, {"GeneralRehearsal/images/lvl3_soldier_attack1.png", "GeneralRehearsal/images/lvl3_soldier_attack2.png", "GeneralRehearsal/images/lvl3_soldier_attack3.png", "GeneralRehearsal/images/lvl3_soldier_attack4.png", "GeneralRehearsal/images/lvl3_soldier_attack5.png"}},
        {60121, {"GeneralRehearsal/images/lvl3_soldier_walking1.png", "GeneralRehearsal/images/lvl3_soldier_walking2.png", "GeneralRehearsal/images/lvl3_soldier_walking3.png"}},
        {60130, {"GeneralRehearsal/images/lvl4_v1_soldier_attack1.png", "GeneralRehearsal/images/lvl4_v1_soldier_attack2.png", "GeneralRehearsal/images/lvl4_v1_soldier_attack3.png", "GeneralRehearsal/images/lvl4_v1_soldier_attack4.png", "GeneralRehearsal/images/lvl4_v1_soldier_attack5.png"}},
        {60131, {"GeneralRehearsal/images/lvl4_v1_soldier_walking1.png", "GeneralRehearsal/images/lvl4_v1_soldier_walking2.png", "GeneralRehearsal/images/lvl4_v1_soldier_walking3.png"}},
        {60140, {"GeneralRehearsal/images/lvl4_v2_soldier_attack1.png", "GeneralRehearsal/images/lvl4_v2_soldier_attack2.png", "GeneralRehearsal/images/lvl4_v2_soldier_attack3.png", "GeneralRehearsal/images/lvl4_v2_soldier_attack4.png", "GeneralRehearsal/images/lvl4_v2_soldier_attack5.png"}},
        {60141, {"GeneralRehearsal/images/lvl4_v2_soldier_walking1.png", "GeneralRehearsal/images/lvl4_v2_soldier_walking2.png", "GeneralRehearsal/images/lvl4_v2_soldier_walking3.png"}},
        {70000, {"GeneralRehearsal/images/wiz_lvl1.png"}},
        {70001, {"GeneralRehearsal/images/wiz_lvl2.png"}},
        {70002, {"GeneralRehearsal/images/wiz_lvl3.png"}},
        {70003, {"GeneralRehearsal/images/wiz_lvl4_v1.png"}},
        {70004, {"GeneralRehearsal/images/wiz_lvl4_v2.png"}},
        {80000, {"GeneralRehearsal/images/arc_lvl1.png"}},
        {80001, {"GeneralRehearsal/images/arc_lvl2.png"}},
        {80002, {"GeneralRehearsal/images/arc_lvl3.png"}},
        {80003, {"GeneralRehearsal/images/arc_lvl4_v1.png"}},
        {80004, {"GeneralRehearsal/images/arc_lvl4_v2.png"}},
        {90000, {"GeneralRehearsal/images/bombard_lvl1.png"}},
        {90001, {"GeneralRehearsal/images/bombard_lvl2.png"}},
        {90002, {"GeneralRehearsal/images/bombard_lvl3.png"}},
        {90003, {"GeneralRehearsal/images/bombard_lvl4_v1.png"}},
        {90004, {"GeneralRehearsal/images/bombard_lvl4_v2.png"}},
        {90015, {"GeneralRehearsal/images/hero1.png", "GeneralRehearsal/images/hero1_attacking1.png", "GeneralRehearsal/images/hero1_attacking2.png", "GeneralRehearsal/images/hero1_attacking3.png", "GeneralRehearsal/images/hero1_attacking4.png", "GeneralRehearsal/images/hero1_attacking5.png"}},
        {90016, {"GeneralRehearsal/images/hero1_walk1.png", "GeneralRehearsal/images/hero1_walk2.png", "GeneralRehearsal/images/hero1_walk3.png"}},
        {99999, {"GeneralRehearsal/images/ground_colors.png"}}};

    for (auto& entry : imagesPaths) {
        int id = entry.first;
        std::vector<std::string> paths = entry.second;

        Row row;
        row.id = id;
        row.texturePaths = paths;

        for (std::string& path : paths) {
            sf::Texture texture;
            if (texture.loadFromFile(path)) {
                row.textures.push_back(texture);
            } else {
                std::cerr << "Error loading texture from path: " << path << std::endl;
            }
        }
        allTexturesMatrix.push_back(row);
    }
}

std::vector<std::vector<int>> Level::getTowerStats() { return towerStats; }
std::vector<std::vector<int>> Level::getTroopStats() { return troopStats; }
std::vector<Row> &Level::getAllTexturesMatrix() { return allTexturesMatrix; }
sf::Texture *Level::getTexturePtr(std::vector<Row> &allTexturesMatrix, int code, int column)
{
    for (auto &row : allTexturesMatrix)
    {
        if (row.id == code && column < row.textures.size())
            return &row.textures[column];
    }
    return nullptr;
}