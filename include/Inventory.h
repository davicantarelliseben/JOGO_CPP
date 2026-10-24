#pragma once
#include "Item.h"
#include <vector>

class Inventory {

    private:
        std::vector<Item> slots;
        unsigned int slotsSize;
        Item bag;
        Item weapon;
    
    public:
        Inventory(std::vector<Item> slots, unsigned int slotsSize, const Item& bag, const Item& weapon);
        bool addItem(const Item& item);
        bool isFull();
        void printInventory();
        void replaceItem(const Item& item);
        void equipWeapon(const Item& newWeapon);
        int getBonusLife() const;
        int getAttack() const;
        int getArmor() const;
        int getSpeed() const;
}; 