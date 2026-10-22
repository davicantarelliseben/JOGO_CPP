#include <Character.h>

void Character::set_life(unsigned int aa){
    this->life = aa;
}
unsigned int Character::get_life(){
    return this->life;
}

void Character::set_damage(unsigned int bb){
    this->damage = bb;
}
unsigned int Character::get_damage(){
    return this->damage;
}

void Character::set_defense(unsigned int cc){
    this->defense = cc;
}
unsigned int Character::get_defense(){
    return this->defense;
}

void Character::set_speed(unsigned int dd){
    this->speed = dd;
}
unsigned int Character::get_speed(){
    return this->speed;
}

Character::Character(unsigned int aa,unsigned int bb,unsigned int cc,unsigned int dd) : life(aa),damage(bb),defense(cc),speed(dd){}