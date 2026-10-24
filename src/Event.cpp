#include "../include/Event.h"

eventType Event::getEventType() {
    return this->type;
}

void Event::triggerEvent(eventType) {
    switch(this->type) {
    case treasureChest:
        break;
    case bladeOils:
        break;
    case campfire:
        break;
    case crystalBall:
        break;
    case forge:
        break;
    case golem:
        break;
    case lookoutTower:
        break;
    case travellingMerchant:
        break;
    case waypoint:
        break;
    case herosGrave:
        break;
    case fairyQueen:
        break;
    case wishingWell:
        break;
    case beehive:
        break;
    case house:
        break;
    case fairy:
        break;
    case jewelryBox:
        break;
    case cauldron:
        break;
    default:
        break;
    }
}