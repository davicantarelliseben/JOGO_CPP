#include "Map.h"

unsigned int Map::countStep() {
    this->stepsCounter--;
    if(this->stepsCounter < 1) {
        cycleDay();
    }
    return this->stepsCounter;
}

void Map::cycleDay() { // algum lugar tem que diminuir os passos, quando zerar chama essa função
    if(this->day) {
        this->day = false;
        this->steps = 30;
    } else {
        this->day = true;
        this->steps = 50;
    }
}