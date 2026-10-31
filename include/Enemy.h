#pragma once
#include "Character.h"

typedef enum { BEAR, SPIDER, WOLF, HEDGEHOG, RAVEN, BAT } enemyType;

class Enemy : public Character {
private:
    enemyType type;
    int level;

public:
    Enemy(int max_life, int currentLife, int attack, int armor, int speed,
          enemyType type, int level);
    
    // Método estático para instanciar um Inimigo aleatório
    static Enemy* createRandomEnemy(int level = 1);

    enemyType getType() const;
    int getLevel() const;
    void Buff(enemyType type);
};