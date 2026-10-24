#pragma once
#include <string>

class Item {
private:
    unsigned int id;
    std::string name;
    std::string rarity;
    int life, attack, armor, speed;

    bool attackOil = false;
    bool armorOil = false;
    bool speedOil = false;

public:
    Item() : id(0), name(""), rarity(""), life(0), attack(0), armor(0), speed(0) {}
    
    Item(unsigned int id, std::string name, std::string rarity, int life, int attack, int armor, int speed)
        : id(id), name(name), rarity(rarity), life(life), attack(attack), armor(armor), speed(speed) {}

    void printItem() const;

    unsigned int getId() const { return id; }
    std::string getName() const { return name; }
    std::string getRarity() const { return rarity; }
    int getLife() const { return life; }
    int getAttack() const { return attack; }
    int getArmor() const { return armor; }
    int getSpeed() const { return speed; }
    bool hasAttackOil() const { return attackOil; }
    bool hasArmorOil() const { return armorOil; }
    bool hasSpeedOil() const { return speedOil; }
    void setOil(int opt);
};