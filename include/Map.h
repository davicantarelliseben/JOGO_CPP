#pragma once
#include "Tiles.h"
#include <vector>

class Map {
    private:
        unsigned int stepsCounter;
        bool day;
        std::vector<std::vector<Tiles>> grid;
    
    public:
        void cycleDay();
        int getSteps();
        unsigned int countStep();
};