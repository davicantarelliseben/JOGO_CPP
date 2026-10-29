#include "Character.h"

Character::Character(int mLife, int cLife, int atk, int armor, int speed)
    : maxLife(mLife), currentLife(cLife), attack(atk), armor(armor), speed(speed) {}

Character::~Character() {}

int Character::getMaxLife() const {
    return this->maxLife;
}

void Character::setMaxLife(int valMaxLife) {
    this->maxLife = valMaxLife;
    if (this->currentLife > this->maxLife) {
        this->currentLife = this->maxLife;
    }
}

int Character::getCurrentLife() const {
    return this->currentLife;
}

void Character::setCurrentLife(int valCurrentLife) {
    if (valCurrentLife > this->maxLife) {
        this->currentLife = this->maxLife;
    } else if (valCurrentLife < 0) {
        this->currentLife = 0;
    } else {
        this->currentLife = valCurrentLife;
    }
}

int Character::getAttack() const {
    return this->attack;
}

void Character::setAttack(int valAttack) {
    this->attack = valAttack;
}

int Character::getArmor() const {
    return this->armor;
}

void Character::setArmor(int valArmor) {
    this->armor = valArmor;
}

int Character::getSpeed() const {
    return this->speed;
}

void Character::setSpeed(int valSpeed) {
    this->speed = valSpeed;
}

bool Character::isAlive() const {
    return this->currentLife > 0;
}

void Character::takeDamage(int dmg) {
    if (dmg <= 0) return;

    if (dmg >= this->currentLife) {
        this->currentLife = 0;
    } else {
        this->currentLife -= dmg;
    }
}
