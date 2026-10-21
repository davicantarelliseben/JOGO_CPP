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
        Inventory();
        bool addItem(const Item& item);
        void equipWeapon(Item* newWeapon);
};