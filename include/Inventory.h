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
        void replaceItem(const Item& item);
        void equipWeapon(Item* newWeapon);
        unsigned int getBonusLife() const;
        unsigned int getAttack() const;
        unsigned int getArmor() const;
        unsigned int getSpeed() const;
}; 