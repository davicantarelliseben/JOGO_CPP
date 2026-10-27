#include "Enemy.h"

Enemy::Enemy(int maxLife, int currentLife, int attack, int armor, int speed,
             enemyType type, unsigned int level)
    : Character(maxLife, currentLife, attack, armor, speed), type(type), level(level) {}

enemyType Enemy::getType() {
    return this->type;
}

unsigned int Enemy::getLevel() {
    return this->level;
}

void Enemy::Buff(enemyType type) {
    switch (type) {
    case BEAR:
        this->attack += 4;
        this->armor += 2;
        break;
    case SPIDER:
        this->speed += 3;
        this->attack += 1;
        break;
    case WOLF:
        this->attack += 2;
        this->speed += 2;
        break;
    case HEDGEHOG:
        this->armor += 4;
        this->speed += 1;
        break;
    case RAVEN:
        this->speed += 5;
        break;
    case BAT:
        this->attack += 3;
        this->speed += 3;
        break;
    }
}
