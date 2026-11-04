#include "Tiles.h"

Tiles::Tiles(bool walkable, Battle* battle, Event* event)
    : walkable(walkable), battle(battle), event(event) {}

bool Tiles::isWalkable() const {
    return walkable;
}

bool Tiles::isBattle() const {
    return battle != nullptr;
}

bool Tiles::isEvent() const {
    return event != nullptr;
}

eventType Tiles::getEventType() const {
    return event == nullptr ? treasureChest : event->getEventType();
}

void Tiles::setWalkable(bool value) {
    walkable = value;
}

void Tiles::setEvent(Event* value) {
    event = value;
}