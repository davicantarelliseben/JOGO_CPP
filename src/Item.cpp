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
        if (attackOil) std::cout << "[Attack Oil (+1)]" << std::endl;
        if (armorOil)  std::cout << "[Armor Oil (+1)]" << std::endl;
        if (speedOil)  std::cout << "[Speed Oil (+1)]" << std::endl;
    }
    std::cout << "-----------------------" << std::endl;
}

void Item::setOil(int opt) {
    if (opt == 0) {
        this->attackOil = false;
        this->armorOil = false;
        this->speedOil = false;
        return;
    }
    this->attackOil = (opt == 1);
    this->armorOil  = (opt == 2);
    this->speedOil  = (opt == 3);
}