#include "Map.h"

unsigned int Map::countStep() {
    this->stepsCounter--;
    if(this->stepsCounter < 1) {
        cycleDay();
    }
    return this->stepsCounter;
}

void Map::cycleDay() {
    if(this->day) {
        this->day = false;
        this->steps = 30;
    } else {
        this->day = true;
        this->steps = 50;
    }
}