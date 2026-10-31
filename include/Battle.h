#pragma once
#include "Player.h"
#include "Enemy.h"

class Battle {
private:
    int turno;
    Player* player;
    Enemy* enemy;

public:
    Battle(Player* player, Enemy* enemy, int turno = 1);
    
    void nextTurn();
    int isBattleOver();
    void calcDamage();
    void battleGoing();
};