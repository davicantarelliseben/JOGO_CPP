#pragma once
#include "Character.h"

typedef enum { BEAR, SPIDER, WOLF, HEDGEHOG, RAVEN, BAT } enemyType;

class Enemy : public Character {

    private:
        enemyType type;
        
        unsigned int level;

    public:
        Enemy(int max_life, int currentLife, int attack, int armor, int speed, enemyType type, unsigned int level);
        enemyType getType();
        unsigned int getLevel();
        void Buff(enemyType type);
};