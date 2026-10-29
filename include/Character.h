#pragma once

class Character {

    protected:
        int maxLife, currentLife, attack, armor, speed;

    public:
        Character(int mLife, int cLife, int atk, int armor, int speed);
        virtual ~Character();
        
        int getMaxLife() const;
        void setMaxLife(int valMaxLife);

        int getCurrentLife() const;
        void setCurrentLife(int valCurrentLife);

        int getAttack() const;
        void setAttack(int valAttack);

        int getArmor() const;
        void setArmor(int valArmor);

        int getSpeed() const;
        void setSpeed(int valSpeed);
        
        bool isAlive() const;
        void takeDamage(int dmg);
};
