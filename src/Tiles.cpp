#include "../include/Tiles.h"

bool Tiles::isWalkable() {
    if(walkable) return true;
    return false;
}

bool Tiles::isBattle() {
    if(battle) return true;
    return false;
}

bool Tiles::isEvent() {
    if(event) return true;
    return false;
}