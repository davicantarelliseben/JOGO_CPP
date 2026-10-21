#include "Battle.h"

Battle::Battle(Player* player, Enemy* enemy, unsigned int turno) : player(player), enemy(enemy), turno(1) {}

void Battle::nextTurn() {
    this->turno++;
}

bool Battle::isBattleOver() {
    if() return 1;
    return 0;
}

void Battle::calcDamage() {
    
}