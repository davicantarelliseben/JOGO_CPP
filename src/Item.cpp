#include "../include/Item.h"
#include <iostream>

void Item::printItem() const {
    // Se for uma Arma, imprime o cabeçalho destacando o nome em vermelho
    if (isWeapon()) {
        std::cout << "--- \033[1;31m" << name << "\033[0m [" << rarity << "] (Arma) ---" << std::endl;
    } else {
        std::cout << "--- " << name << " [" << rarity << "] (Item) ---" << std::endl;
    }
    
    std::cout << "ID: " << id << std::endl;

    // Usando os getters para refletir os atributos com os óleos aplicados (se houver)
    int totalAtk = getAttack();
    int totalArm = getArmor();
    int totalSpd = getSpeed();

    if (life != 0)     std::cout << "Life: "   << (life > 0 ? "+" : "")   << life << std::endl;
    if (totalAtk != 0) std::cout << "Attack: " << (totalAtk > 0 ? "+" : "") << totalAtk << std::endl;
    if (totalArm != 0) std::cout << "Armor: "  << (totalArm > 0 ? "+" : "")  << totalArm << std::endl;
    if (totalSpd != 0) std::cout << "Speed: "  << (totalSpd > 0 ? "+" : "")  << totalSpd << std::endl;

    if (hasAttackOil() || hasArmorOil() || hasSpeedOil()) {
        std::cout << "Applied Oil: ";
        if (hasAttackOil()) std::cout << "[Attack Oil (+1)] ";
        if (hasArmorOil())  std::cout << "[Armor Oil (+1)] ";
        if (hasSpeedOil())  std::cout << "[Speed Oil (+1)] ";
        std::cout << std::endl;
    }
    std::cout << "-----------------------" << std::endl;
}

bool Item::applyOil(int opt) {
    if (opt == 1) {
        if (this->attackOil) return false;
        this->attackOil = true;
        return true;
    }
    if (opt == 2) {
        if (this->armorOil) return false;
        this->armorOil = true;
        return true;
    }
    if (opt == 3) {
        if (this->speedOil) return false;
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

bool Item::setOil(int opt) {
    if (opt == 0) {
        clearOils();
        return true;
    }
    return applyOil(opt);
}