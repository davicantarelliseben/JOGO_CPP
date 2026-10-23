#pragma once
#include <string>

class Item {

    private:
        std::string name;
        unsigned int life, attack, armor, speed;
        bool attackOil, armorOil, speedOil;
    
    public:
        Item(std::string name, unsigned int life, unsigned int attack, unsigned int armor, unsigned int speed);
        void printItem() const;
        std::string getName() const;
        unsigned int getLife() const;
        unsigned int getAttack() const;
        unsigned int getArmor() const;
        unsigned int getSpeed() const;
        bool getAttackOil() const;
        bool getArmorOil() const;
        bool getSpeedOil() const;
        void setOil(int opt);
};