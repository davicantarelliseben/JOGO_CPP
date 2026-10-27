#pragma once
#include <string>

class Item {

    private:
        std::string name;
        unsigned int life, attack, armor, speed;
    
    public:
        Item(std::string nome,unsigned int life, unsigned int attack, unsigned int armor, unsigned int speed);
        void printItem();
        std::string getName();
        unsigned int getLife();
        unsigned int getAttack();
        unsigned int getArmor();
        unsigned int getSpeed();
};