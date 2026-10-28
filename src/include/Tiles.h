#pragma once
#include "Battle.h"
#include "Event.h"

class Tiles {
private:
    bool walkable;
    Battle* battle;
    Event* event;

public:
    Tiles(bool walkable = true, Battle* battle = nullptr, Event* event = nullptr);
    bool isWalkable();
    bool isBattle();
    bool isEvent();
};