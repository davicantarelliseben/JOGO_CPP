#pragma once
#include "Character.h"

typedef enum { BEAR, SPIDER, WOLF, HEDGEHOG, RAVEN, BAT } enemyType;

class Enemy : public Character {

    private:
        enemyType type;
        
        unsigned int level;

    public:
        Enemy(unsigned int max_life, unsigned int currentLife, unsigned int attack, unsigned int armor, unsigned int speed, enemyType type, unsigned int level);
        enemyType getType();
        unsigned int getLevel();
        void Buff(enemyType type);
};