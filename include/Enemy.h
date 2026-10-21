#pragma once
#include "Character.h"

typedef enum { URSO, ARANHA, LOBO, MORCEGO, HEDGEHOG, CORVO, COBRA, SAPO, CASTOR, LIBELULA, GUARDAS_DO_PALACIO, SLIME, TARTARUGA, ABELHA, GUAXINIM } enemyType;

typedef enum { CAVALEIRO_DAS_TREVAS, LESHEN, URSO_GARRAFIADA, SILKWEAVER_QUEEN, FUNGAL_GIANT, SWAMPLAND_HYDRA } bossType;

class Enemy : public Character {

    private:
        enemyType type;
        bossType boss;
        unsigned int level;

    public:
        Enemy();
        enemyType getType();
        bossType getBoss();
        unsigned int getLevel();
        void Buff(enemyType type);
};