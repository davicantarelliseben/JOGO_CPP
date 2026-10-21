#pragma once
#include "Player.h"
#include "Enemy.h"

class Battle {
    private:
        unsigned int turno;
        Player* player;
        Enemy* enemy;
        
    public:
        Battle(Player* player, Enemy* enemy, unsigned int turno);
        void nextTurn();
        bool isBattleOver();
        void calcDamage();
};