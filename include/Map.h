#pragma once
#include "Tiles.h"
#include <vector>

class Map {
    private:
        bool day;
        std::vector<std::vector<Tiles>> grid;
    
    public:
        void dayToNight();
};