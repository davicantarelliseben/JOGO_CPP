#pragma once
#include "Tiles.h"
#include <vector>

class Map {
private:
    int stepsCounter;
    bool day;
    std::vector<std::vector<Tiles>> grid;
    int altura = 0;
    int largura = 0;

public:
    Map(int stepsCounter = 30, bool day = true);
    void cycleDay();
    int getSteps();
    int countStep();
    bool isDay() const;
    void addSteps(int val);
    void setSteps(int val);
    void revealAroundPlayer(int radius = 3);
    void populateEventsAndBattles(int playerY, int playerX, Player* player, ItemManager* itemManager);
    void printMap();
    bool loadFromFile(const std::string& filename);

};