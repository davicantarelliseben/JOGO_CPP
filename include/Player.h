#pragma once
#include "Character.h"
#include "Inventory.h"

class Player : public Character {

    private:
        unsigned int coins;
        Inventory inventory;
    
    public:
        Player(int maxLife, int currentLife, int attack, int armor, int speed, unsigned int coins, Inventory inventory);
        ~Player();
        void addCoins(unsigned int amount);
};