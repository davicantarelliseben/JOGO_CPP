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
    void setWalkable(bool v);
    bool isWalkable();
    bool isBattle();
    bool isEvent();

    Event* getEvent();
    Battle* getBattle();
    void setEvent(Event* newEvent);
    void setBattle(Battle* newBattle);
};
