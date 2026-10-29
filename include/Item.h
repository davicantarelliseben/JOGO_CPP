#pragma once
#include <string>

class Item {
private:
    int id;
    std::string name;
    std::string rarity;
    int life, attack, armor, speed;

    bool attackOil = false;
    bool armorOil = false;
    bool speedOil = false;

public:
    Item() : id(0), name(""), rarity(""), life(0), attack(0), armor(0), speed(0) {}
    
    Item(int id, std::string name, std::string rarity, int life, int attack, int armor, int speed)
        : id(id), name(name), rarity(rarity), life(life), attack(attack), armor(armor), speed(speed) {}

    void printItem() const;

    int getId() const { return id; }
    std::string getName() const { return name; }
    std::string getRarity() const { return rarity; }
    int getLife() const { return life; }
    int getAttack() const { return attack + (attackOil ? 1 : 0); }
    int getArmor() const { return armor + (armorOil ? 1 : 0); }
    int getSpeed() const { return speed + (speedOil ? 1 : 0); }
    int getBaseAttack() const { return attack; }
    int getBaseArmor() const { return armor; }
    int getBaseSpeed() const { return speed; }

    bool hasAttackOil() const { return attackOil; }
    bool hasArmorOil() const { return armorOil; }
    bool hasSpeedOil() const { return speedOil; }

    // Aplica um oleo na arma; nao permite repetir o mesmo oleo
    bool applyOil(int opt);
    bool setOil(int opt);
    void clearOils();

    void setName(const std::string& newName) { name = newName; }
    void setRarity(const std::string& newRarity) { rarity = newRarity; }
    void setLife(int newLife) { life = newLife; }
    void setAttack(int newAttack) { attack = newAttack; }
    void setArmor(int newArmor) { armor = newArmor; }
    void setSpeed(int newSpeed) { speed = newSpeed; }
    void upgrade(int dLife, int dAtk, int dArm, int dSpd) {
        life += dLife;
        attack += dAtk;
        armor += dArm;
        speed += dSpd;
    }
};
