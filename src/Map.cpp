#include "Map.h"
#include <iostream>

Map::Map(int stepsCounter, bool day)
    : stepsCounter(stepsCounter), day(day) {}

int Map::countStep() {
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
    return stepsCounter;
}

bool Map::isDay() const {
    return day;
}

void Map::addSteps(int val) {
    stepsCounter += val;
}

void Map::setSteps(int val) {
    stepsCounter = val;
}

void Map::revealAroundPlayer(int radius) {
    std::cout << "[Visao do Mapa]: Area em torno do jogador revelada (raio de " << radius << " tiles)!\n";
    std::cout << "[Visao do Mapa]: Periodo: " << (day ? "Dia (claro e visivel)" : "Noite (perigosa e escura)")
              << " | Passos restantes: " << stepsCounter << "\n";
}
