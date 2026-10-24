#pragma once

class Character {

    private:
        int maxLife, currentLife, attack, armor, speed;

    public:
        Character(int mLife, int cLife, int atk, int armor, int speed);
        ~Character();
        int getMaxLife();
        int getCurrentLife();
        int getAttack();
        int getArmor();
        int getSpeed();
        bool isAlive();
        void takeDamage(unsigned int damage);
};