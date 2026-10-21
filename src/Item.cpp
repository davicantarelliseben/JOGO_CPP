#include "Item.h"
#include <iostream>

Item::Item(unsigned int life, unsigned int attack, unsigned int armor, unsigned int speed) : life(life), attack(attack), armor(armor), speed(speed) {}

void Item::printItem() {
    std::cout << life << std::endl;
    std::cout << attack << std::endl;
    std::cout << armor << std::endl;
    std::cout << speed << std::endl; 
}

std::string Item::getName() {
    return this->name;
}

unsigned int Item::getLife() {
    return this->life;
}

unsigned int Item::getAttack() {
    return this->attack;
}

unsigned int Item::getArmor() {
    return this->armor;
}

unsigned int Item::getSpeed() {
    return this->speed;
}