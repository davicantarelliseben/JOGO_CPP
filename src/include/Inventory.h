#pragma once
#include "Item.h"
#include <vector>

class Inventory {

    private:
        std::vector<Item> slots;
        unsigned int slotsSize;
        Item* bag;
        Item* weapon;
    
    public:
        Inventory(std::vector<Item> slots, unsigned int slotsSize, Item* bag, Item* weapon);
        bool addItem(const Item& item);
        bool isFull();
        void printInventory();
        bool replaceItem(const Item& item);
        void equipWeapon(Item* newWeapon);
        unsigned int getBonusLife();
        unsigned int getAttack();
        unsigned int getArmor();
        unsigned int getSpeed();
}; 