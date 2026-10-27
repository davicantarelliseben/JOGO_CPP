#include "include/Character.h"

Character::Character(unsigned int mLife, unsigned int cLife, unsigned int atk, unsigned int armor, unsigned int speed) : maxLife(mLife), currentLife(cLife), attack(atk), armor(armor), speed(speed) {}

Character::~Character() {}

unsigned int Character::getMaxLife() {
    return this->maxLife;
}

void Character::setMaxLife(unsigned int valMaxLife) {
    this-> maxLife = valMaxLife;
}

unsigned int Character::getCurrentLife() {
    return this->currentLife;
}

void Character::setCurrentLife(unsigned int valCurrentLife) {
    if(valCurrentLife > this->maxLife){
        this->currentLife = this->maxLife;
    }else {
    this-> currentLife = valCurrentLife;
    }
}

unsigned int Character::getAttack() {
    return this->attack;
}

void Character::setAttack(unsigned int valAttack) {
    this->attack = valAttack;
}

unsigned int Character::getArmor() {
    return this->armor;
}

void Character::setArmor(unsigned int valArmor) {
    this->armor = valArmor;
}

unsigned int Character::getSpeed() {
    return this->speed;
}

void Character::setSpeed(unsigned int valSpeed) {
    this->speed = valSpeed;
}

bool Character::isAlive() {
    if(this->currentLife == 0) {
        return 0;
    }
    return 1;
}

void Character::takeDamage(unsigned int& dmg) {
    unsigned int damage = getAttack();

  if(damage >= this->currentLife){
            this->currentLife = 0;
    }else {
        this->currentLife -= damage;
    }
}