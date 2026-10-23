#include "Map.h"

int Map::getSteps() {
    return this->steps;
}

void Map::cycleDay() { // algum lugar tem que diminuir os passos, quando zerar chama essa função
    if(day) {
        day = false;
        steps = 30;
    } else {
        day = true;
        steps = 50;
    }
}