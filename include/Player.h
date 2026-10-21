#pragma once
#include "Character.h"
#include "Inventory.h"

class Player : public Character {

    private:
        unsigned int coins;
        Inventory inventory;
    
    public:
        Player();
        ~Player();
        void addCoins(unsigned int amount);
};