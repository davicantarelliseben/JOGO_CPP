#pragma once
#include <string>

class Player;
class ItemManager;
class Map;

typedef enum {
    treasureChest,
    bladeOils,
    campfire,
    forge,
    golem,
    lookoutTower,
    travellingMerchant
} eventType;

class Event {
    private:
        eventType type;
        Player* player;
        ItemManager* itemManager;
        Map* map;
        bool interactive;

        void handleTreasureChest();
        void handleBladeOils();
        void handleCampfire();
        void handleForge();
        void handleGolem();
        void handleLookoutTower();
        void handleTravellingMerchant();
        
    public:
        Event(eventType type = treasureChest, Player* player = nullptr, ItemManager* itemManager = nullptr, Map* map = nullptr, bool interactive = false);
        static Event* createRandomEvent(Player* player = nullptr, ItemManager* itemManager = nullptr, Map* map = nullptr, bool interactive = true);

        eventType getEventType() const;
        void setEventType(eventType type);

        void setPlayer(Player* p);
        void setItemManager(ItemManager* im);
        void setMap(Map* m);
        void setInteractive(bool active);
        bool isInteractive() const;

        void triggerEvent(eventType type);
        void triggerEvent(Player& p, ItemManager* im = nullptr, Map* m = nullptr);
        void triggerEvent(eventType type, Player& p, ItemManager* im = nullptr, Map* m = nullptr);
};
