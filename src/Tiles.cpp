#include "../include/Tiles.h"

Tiles::Tiles(bool walkable, Battle* battle, Event* event)
    : walkable(walkable), battle(battle), event(event) {}

void Tiles::setWalkable(bool v) {
    this->walkable = v;
}

bool Tiles::isWalkable() {
    return walkable;
}

bool Tiles::isBattle() {
    return battle != nullptr;
}

bool Tiles::isEvent() {
    return event != nullptr;
}

Event* Tiles::getEvent() {
    return event;
}

Battle* Tiles::getBattle() {
    return battle;
}

void Tiles::setEvent(Event* newEvent) {
    event = newEvent;
}

void Tiles::setBattle(Battle* newBattle) {
    battle = newBattle;
}
