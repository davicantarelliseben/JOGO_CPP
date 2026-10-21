#pragma once
#include <string>

class Item {

    private:
        std::string name;
        unsigned int life, attack, armor, speed;
    
    public:
        Item();
        std::string getName();
        unsigned int getBonus();
};