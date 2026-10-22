#pragma once
#include <string>

class Item {

    private:
        std::string name;
        unsigned int life, attack, armor, speed;
    
    public:
        Item(std::string name, unsigned int life, unsigned int attack, unsigned int armor, unsigned int speed);
        void printItem() const;
        std::string getName() const;
        unsigned int getLife() const;
        unsigned int getAttack() const;
        unsigned int getArmor() const;
        unsigned int getSpeed() const;
};