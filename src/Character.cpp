#include "Character.h"

Character::Character(int mLife, int cLife, int atk, int armor, int speed) : maxLife(maxLife), currentLife(currentLife), attack(attack), armor(armor), speed(speed) {}

Character::~Character() {}

int Character::getMaxLife() {
    return this->maxLife;
}

int Character::getCurrentLife() {
    return this->currentLife;
}

int Character::getAttack() {
    return this->attack;
}

int Character::getArmor() {
    return this->armor;
}

int Character::getSpeed() {
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