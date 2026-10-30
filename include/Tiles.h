#pragma once
#include "Battle.h"
#include "Event.h"

class Tiles {
private:
    bool walkable;
    Battle* battle;
    Enemy* enemy;
    Event* event;

public:
    Tiles(bool walkable = true, Battle* battle = nullptr, Event* event = nullptr, Enemy* enemy = nullptr);
    void setWalkable(bool v);
    bool isWalkable();
    bool isBattle();
    bool isEnemy();
    bool isEvent();

    Event* getEvent();
    Battle* getBattle();
    Enemy* getEnemy();
    void setEvent(Event* newEvent);
    void setBattle(Battle* newBattle);
    void setEnemy(Enemy* newEnemy);
};
