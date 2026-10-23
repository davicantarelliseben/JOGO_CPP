#pragma once
#include "Tiles.h"
#include <vector>

class Map {
    private:
        int steps;
        bool day;
        std::vector<std::vector<Tiles>> grid;
    
    public:
        void cycleDay();
        int getSteps();
};