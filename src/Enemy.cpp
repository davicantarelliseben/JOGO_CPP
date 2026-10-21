#include "Enemy.h"

Enemy::Enemy() : type(type), boss(boss), level(level) {}

enemyType Enemy::getType() {
    return this->type;
}

bossType Enemy::getBoss() {
    return this->boss;
}

unsigned int Enemy::getLevel() {
    return this->level;
}

void Enemy::Buff(enemyType type) {
    switch(type) {

        case URSO:
            
            break;
        case ARANHA:

            break;
        case LOBO:

            break;
        case MORCEGO:

            break;
        case HEDGEHOG:

            break;
        case CORVO:

            break;
        case COBRA:
     
            break;
        case SAPO:

            break;
        case CASTOR:

            break;
        case LIBELULA:

            break;
        case GUARDAS_DO_PALACIO:

            break;
        case SLIME:

            break;
        case TARTARUGA:

            break;
        case ABELHA:

            break;
        case GUAXINIM:

            break;
    }
}

