#include "Character.h"

Character::Character() : maxLife(maxLife), currentLife(currentLife), attack(attack), armor(armor), speed(speed) {}

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
    if(this->currentLife == 0) {
        return 0;
    }
    return 1;
}

void Character::takeDamage(unsigned int damage) {
    this->currentLife -= damage;
}