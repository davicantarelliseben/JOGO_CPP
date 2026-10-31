#include "../include/Tiles.h"

Tiles::Tiles(bool walkable, Battle* battle, Event* event, Enemy* enemy, TileState state)
    : walkable(walkable), battle(battle), enemy(enemy), event(event), state(state) {}

void Tiles::setWalkable(bool v) {
    this->walkable = v;
}

bool Tiles::isWalkable() {
    return this->walkable;
}

bool Tiles::isBattle() {
    return battle != nullptr;
}

bool Tiles::isEnemy() {
    return enemy != nullptr;
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

Enemy* Tiles::getEnemy() {
    return enemy;
}

void Tiles::setEvent(Event* newEvent) {
    event = newEvent;
}

void Tiles::setBattle(Battle* newBattle) {
    battle = newBattle;
}

void Tiles::setEnemy(Enemy* newEnemy) {
    enemy = newEnemy;
}

TileState Tiles::getState() const {
    return state;
}

void Tiles::setState(TileState newState) {
    state = newState;
}