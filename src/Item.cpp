#include "Item.h"
#include <iostream>

void Item::printItem() const {
    std::cout << "--- " << name << " [" << rarity << "] ---" << std::endl;
    std::cout << "ID: " << id << std::endl;

    //se for stats negativo devolve -2, tem item que faz isso(espada de 4 attack -2 speed)
    if (life != 0)   std::cout << "Life: "   << (life > 0 ? "+" : "")   << life << std::endl;
    if (attack != 0) std::cout << "Attack: " << (attack > 0 ? "+" : "") << attack << std::endl;
    if (armor != 0)  std::cout << "Armor: "  << (armor > 0 ? "+" : "")  << armor << std::endl;
    if (speed != 0)  std::cout << "Speed: "  << (speed > 0 ? "+" : "")  << speed << std::endl;

    if (attackOil || armorOil || speedOil) {
        std::cout << "Applied Oil: ";
        if (attackOil) std::cout << "[Attack Oil (+1)] ";
        if (armorOil)  std::cout << "[Armor Oil (+1)] ";
        if (speedOil)  std::cout << "[Speed Oil (+1)] ";
        std::cout << std::endl;
    }
    std::cout << "-----------------------" << std::endl;
}

bool Item::applyOil(int opt) {
    if (opt == 1) {
        if (this->attackOil) return false; // Nao pode repetir o mesmo oleo
        this->attackOil = true;
        return true;
    }
    if (opt == 2) {
        if (this->armorOil) return false; // Nao pode repetir o mesmo oleo
        this->armorOil = true;
        return true;
    }
    if (opt == 3) {
        if (this->speedOil) return false; // Nao pode repetir o mesmo oleo
        this->speedOil = true;
        return true;
    }
    return false;
}

void Item::clearOils() {
    this->attackOil = false;
    this->armorOil  = false;
    this->speedOil  = false;
}

void Item::setOil(int opt) {
    if (opt == 0) {
        clearOils();
        return;
    }
    applyOil(opt);
}
