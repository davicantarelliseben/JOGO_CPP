#pragma once

class Character {

    private:
        unsigned int maxLife, currentLife, attack, armor, speed;

    public:
        Character();
        ~Character();
        unsigned int getMaxLife();
        unsigned int getCurrentLife();
        unsigned int getAttack();
        unsigned int getArmor();
        unsigned int getSpeed();
        bool isAlive();
        void takeDamage(unsigned int damage);
};