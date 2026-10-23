#pragma once

typedef enum { treasureChest, bladeOils, campfire, crystalBall, forge, golem, 
    lookoutTower, travellingMerchant, waypoint, herosGrave, fairyQueen, 
    wishingWell, beehive, house, fairy, jewelryBox, cauldron } eventType;

class Event {
    private:
        eventType type;

    public:
        eventType getEventType();
        void triggerEvent(eventType type);
};