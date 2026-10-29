#pragma once
#include "Tiles.h"
#include <vector>

class Map {
private:
    int stepsCounter;
    bool day;
    std::vector<std::vector<Tiles>> grid;

public:
    Map(int stepsCounter = 30, bool day = true);
    void cycleDay();
    int getSteps();
    int countStep();

    bool isDay() const;
    void addSteps(int val);
    void setSteps(int val);
    void revealAroundPlayer(int radius = 3);
};
