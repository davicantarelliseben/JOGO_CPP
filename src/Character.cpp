#include "Character.h"

Character::Character(unsigned int mLife, unsigned int cLife, unsigned int atk, unsigned int armor, unsigned int speed) : maxLife(maxLife), currentLife(currentLife), attack(attack), armor(armor), speed(speed) {}

Character::~Character() {}

unsigned int Character::getMaxLife() {
    return this->maxLife;
}

unsigned int Character::getCurrentLife() {
    return this->currentLife;
}

unsigned int Character::getAttack() {
    return this->attack;
}

unsigned int Character::getArmor() {
    return this->armor;
}

unsigned int Character::getSpeed() {
    return this->speed;
}

bool Character::isAlive() {
    if(this->currentLife < 1) { //mudei a condição de ==0 pra < 1
        return 0;
    }
    return 1;
}

void Character::takeDamage(unsigned int damage) {
    if(damage > this->currentLife) {
        //alguma função do tipo kill()
    } else {
        this->currentLife -= damage;
    }
}