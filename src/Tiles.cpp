#include "Tiles.h"

Tiles::Tiles(bool walkable, Battle* battle, Event* event)
    : walkable(walkable), battle(battle), event(event) {}

bool Tiles::isWalkable() {
    return walkable;
}

bool Tiles::isBattle() {
    return battle != nullptr;
}

bool Tiles::isEvent() {
    return event != nullptr;
}