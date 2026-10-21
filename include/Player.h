#pragma once
#include "Character.h"
#include "Inventory.h"

class Player : public Character {

    private:
        unsigned int coins;
        Inventory inventory;
    
    public:
        Player(unsigned int maxLife, unsigned int currentLife, unsigned int attack, unsigned int armor, unsigned int speed, unsigned int coins, Inventory inventory);
        ~Player();
        void addCoins(unsigned int amount);
};