#pragma once
#include "Battle.h"
#include "Event.h"

class Tiles {
    private:
        bool Walkable;
        Battle* battle;
        Event* event;
    
    public:
        bool isWalkable();
        bool isBattle();
        bool isEvent();
};