#include "../include/Enemy.h"

Enemy::Enemy(int max_life, int currentLife, int attack, int armor, int speed,
             enemyType type, int level)
    : Character(max_life, currentLife, attack, armor, speed),
      type(type), level(level) {}

enemyType Enemy::getType() const {
    return this->type;
}

int Enemy::getLevel() const {
    return this->level;
}

void Enemy::Buff(enemyType t) {
    this->type = t;
    switch (this->type) {
    case BEAR:
        this->attack += 3;
        this->armor += 1;
        break;
    case SPIDER:
        this->speed += 2;
        break;
    case WOLF:
        this->attack += 2;
        this->speed += 1;
        break;
    case HEDGEHOG:
        this->armor += 3;
        break;
    case RAVEN:
        this->speed += 3;
        break;
    case BAT:
        this->speed += 2;
        break;
    }
}
