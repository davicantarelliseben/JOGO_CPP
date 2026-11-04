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
    bool isWalkable() const;
    bool isBattle() const;
    bool isEvent() const;
    eventType getEventType() const;
    void setWalkable(bool value);
    void setEvent(Event* value);
};