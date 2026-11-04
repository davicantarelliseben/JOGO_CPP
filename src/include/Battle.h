#pragma once
#include "Player.h"
#include "Enemy.h"

class Battle {
private:
    unsigned int turno;
    Player* player;
    Enemy* enemy;
    unsigned int playerShield;
    unsigned int enemyShield;

public:
    Battle(Player* player, Enemy* enemy, unsigned int turno);
    void nextTurn();
    int isBattleOver();
    void calcDamage();
    void battleGoing();
    void playerAttack();
    void enemyAttack();
    unsigned int getPlayerShield() const;
    unsigned int getEnemyShield() const;
    unsigned int getTurn() const;
    bool isPlayerFirst() const;
};