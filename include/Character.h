#ifndef CHARACTER_H_
#define CHARACTER_H_

class Character {
private :
    unsigned int life;
    unsigned int damage;
    unsigned int defense;
    unsigned int speed;

public :

    void set_life(unsigned int aa);
    unsigned int get_life();

    void set_damage(unsigned int aa);
    unsigned int get_damage();

    void set_defense(unsigned int aa);
    unsigned int get_defense();

    void set_speed(unsigned int aa);
    unsigned int get_speed();

    Character(unsigned int aa,unsigned int bb,unsigned int cc,unsigned int dd) : life(aa),damage(bb),defense(cc),speed(dd){};

};

#endif