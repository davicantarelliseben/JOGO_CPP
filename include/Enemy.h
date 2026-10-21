#pragma once
#include "Character.h"

typedef enum { URSO, ARANHA, LOBO, MORCEGO, HEDGEHOG, CORVO, COBRA, SAPO, CASTOR, LIBELULA, GUARDAS_DO_PALACIO, SLIME, TARTARUGA, ABELHA, GUAXINIM, CAVALEIRO_DAS_TREVAS, LESHEN, URSO_GARRAFIADA, SILKWEAVER_QUEEN, FUNGAL_GIANT, SWAMPLAND_HYDRA } enemyType;

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