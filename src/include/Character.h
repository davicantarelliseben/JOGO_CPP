#pragma once

class Character {

    protected:
        unsigned int maxLife, currentLife, attack, armor, speed;

    public:
        Character(unsigned int mLife, unsigned int cLife, unsigned int atk, unsigned int armor, unsigned int speed);
        ~Character();
        
        unsigned int getMaxLife();
        void setMaxLife(unsigned int valMaxLife);

        unsigned int getCurrentLife();
        void setCurrentLife(unsigned int valCurrentLife);

        unsigned int getAttack();
        void setAttack(unsigned int valAttack);

        unsigned int getArmor();
        void setArmor(unsigned int valArmor);

        unsigned int getSpeed();
        void setSpeed(unsigned int valSpeed);
        

        bool isAlive();
        void takeDamage(unsigned int damage);

};