#pragma once

class Character {

    private:
        unsigned int maxLife, currentLife, attack, armor, speed;

    public:
        Character(unsigned int mLife, unsigned int cLife, unsigned int atk, unsigned int armor, unsigned int speed);
        ~Character();

        unsigned int getMaxLife();
        void setMaxLife();

        unsigned int getCurrentLife();
        void setCurrentLife();

        unsigned int getAttack();
        void setAttack();

        unsigned int getArmor();
        void setArmor();

        unsigned int getSpeed();
        void setSpeed();


        bool isAlive();
        void takeDamage(unsigned int damage);
};