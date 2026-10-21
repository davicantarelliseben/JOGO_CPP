#pragma once

class Character {

    private:
        unsigned int maxLife, currentLife, attack, armor, speed;

    public:
        Character(unsigned int mLife, unsigned int cLife, unsigned int atk, unsigned int armor, unsigned int speed);
        ~Character();
        unsigned int getMaxLife();
        unsigned int getCurrentLife();
        unsigned int getAttack();
        unsigned int getArmor();
        unsigned int getSpeed();
        bool isAlive();
        void takeDamage(unsigned int damage);
};