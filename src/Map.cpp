#include "Map.h"

Map::Map(unsigned int stepsCounter, bool day)
    : stepsCounter(stepsCounter), day(day) {}

unsigned int Map::countStep() {
    if (stepsCounter == 0) {
        cycleDay();
    }

    --stepsCounter;
    if (stepsCounter == 0) {
        cycleDay();
    }
    return stepsCounter;
}

void Map::cycleDay() {
    if (this->day) {
        this->day = false;
        this->stepsCounter = 30;
    } else {
        this->day = true;
        this->stepsCounter = 50;
    }
}

int Map::getSteps() {
    return static_cast<int>(stepsCounter);
}