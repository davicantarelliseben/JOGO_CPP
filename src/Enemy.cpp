#include <Enemy.h>

Enemy::Enemy(unsigned int maxLife, unsigned int currentLife, unsigned int attack, unsigned int armor, unsigned int speed, enemyType type, unsigned int level)
    : Character(maxLife, currentLife, attack, armor, speed), type(type), level(level) {}

enemyType Enemy::getType() {
    return this->type;
}
unsigned int Enemy::getLevel() {
    return this->level;
}

void Enemy::Buff(enemyType type) {
    switch(type) {

        case BEAR:

            this->maxLife += 10;
            this->attack += 2;
            
            break;

        case SPIDER:
            this->speed += 5;
            this->attack += 8;
            break;

        case WOLF:
            this->attack += 10;
            this->speed += 2;
            break;

        //case MORCEGO:
            
        //    break;
        //case HEDGEHOG:

        //    break;
        //case CORVO:

        //    break;
        //case COBRA:
     
        //    break;
        //case SAPO:

        //    break;
        //case CASTOR:

        //    break;
        //case LIBELULA:

        //    break;
        //case GUARDAS_DO_PALACIO:

        //    break;
        //case SLIME:

        //    break;
        //case TARTARUGA:

        //    break;
        //case ABELHA:

        //    break;
        //case GUAXINIM:

        //    break;
    }
}

