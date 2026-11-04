#pragma once
#include "Tiles.h"
#include <memory>
#include <vector>

class Map {
private:
    unsigned int stepsCounter;
    bool day;
    std::vector<std::vector<Tiles>> grid;
    std::vector<std::unique_ptr<Event>> events;

public:
    Map(unsigned int stepsCounter = 30, bool day = true);
    void cycleDay();
    int getSteps();
    unsigned int countStep();
    bool isDay() const;
    unsigned int getWidth() const;
    unsigned int getHeight() const;
    bool isWalkable(int x, int y) const;
    bool isEvent(int x, int y) const;
    eventType getEventType(int x, int y) const;
    void setWalkable(int x, int y, bool walkable);
    void setEvent(int x, int y, eventType type);
};