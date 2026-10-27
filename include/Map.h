#pragma once
#include "Tiles.h"
#include <vector>

class Map {
private:
    unsigned int stepsCounter;
    bool day;
    std::vector<std::vector<Tiles>> grid;

public:
    Map(unsigned int stepsCounter = 30, bool day = true);
    void cycleDay();
    int getSteps();
    unsigned int countStep();
};