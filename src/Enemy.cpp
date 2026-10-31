#include "../include/Enemy.h"
#include <random>

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

Enemy* Enemy::createRandomEnemy(int level) {
    static std::random_device rd;
    static std::mt19937 gen(rd());

    // Sorteia entre 0 e 5 (correspondente a BEAR, SPIDER, WOLF, HEDGEHOG, RAVEN, BAT)
    std::uniform_int_distribution<int> dist(0, 5);
    enemyType randomType = static_cast<enemyType>(dist(gen));

    // Status base ajustados pelo nível
    int baseHp = 15 + (level * 5);
    int baseAtk = 2 + (level * 2);
    int baseArm = 1 + level;
    int baseSpd = 3 + level;

    // Instancia o inimigo com os status base
    Enemy* enemy = new Enemy(baseHp, baseHp, baseAtk, baseArm, baseSpd, randomType, level);

    // Aplica as bonificações únicas de classe definidas no método Buff
    enemy->Buff(randomType);

    return enemy;
}