#include "Item.h"
#include <iostream>

Item::Item(std::string name, unsigned int life, unsigned int attack, unsigned int armor, unsigned int speed) : name(name), life(life), attack(attack), armor(armor), speed(speed) {}

void Item::printItem() const{
    std::cout << life << std::endl;
    std::cout << attack << std::endl;
    std::cout << armor << std::endl;
    std::cout << speed << std::endl; 
}

std::string Item::getName() const {
    return this->name;
}

unsigned int Item::getLife() const {
    return this->life;
}

unsigned int Item::getAttack() const {
    return this->attack;
}

unsigned int Item::getArmor() const {
    return this->armor;
}

unsigned int Item::getSpeed() const {
    return this->speed;
}