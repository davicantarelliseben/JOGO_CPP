#include "Enemy.h"

Enemy::Enemy(int maxLife, int currentLife, int attack, int armor, int speed, enemyType type, unsigned int level)
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
            
            break;
        case SPIDER:

            break;
        case WOLF:

            break;
        case HEDGEHOG:

            break;
        case RAVEN:

            break;
        case BAT:
     
            break;
    }
}

