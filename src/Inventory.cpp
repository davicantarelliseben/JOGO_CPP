#include "Inventory.h"
#include <iostream>

Inventory::Inventory(std::vector<Item> slots, unsigned int slotsSize, const Item& bag, const Item& weapon) 
    : slots(slots), slotsSize(slotsSize), bag(bag), weapon(weapon) {}

bool Inventory::isFull() {
    return slots.size() == slotsSize;
}

void Inventory::printInventory() {
    for(int i = 0; i < slots.size(); i++) {
        const Item& temp = slots.at(i);
        temp.printItem();
    }
}

void Inventory::replaceItem(const Item& item) {
    this->printInventory();
    int indiceRemovido;
    std::cout << "Escolha o item a ser removido: " << std::endl;
    std::cin >> indiceRemovido;
    // item = slots.at(indiceRemovido);
}

bool Inventory::addItem(const Item& item) {
    if(this->isFull()) {
        this->replaceItem(item);
        return false;
    }
    this->slots.push_back(item);
    return true;
}

int Inventory::getBonusLife() const {
    int addLife = 0;
    for(int i = 0; i < slots.size(); i++) {
        const Item& temp = slots.at(i);
        addLife += temp.getLife();
    }
    return addLife;
}

int Inventory::getAttack() const {
    int addAttack = 0;

    for(int i = 0; i < slots.size(); i++) {
        const Item& temp = slots.at(i);
        addAttack += temp.getAttack();
    }
    addAttack += this->weapon.getAttack();

    if(this->weapon.hasAttackOil()) addAttack += 1;

    return addAttack;
}

int Inventory::getArmor() const {
    int addArmor = 0;

    for(int i = 0; i < slots.size(); i++) {
        const Item& temp = slots.at(i);
        addArmor += temp.getArmor();
    }
    addArmor += this->weapon.getArmor();

    if(this->weapon.hasArmorOil()) addArmor += 1;

    return addArmor;
}

int Inventory::getSpeed() const {
    int addSpeed = 0;

    for(int i = 0; i < slots.size(); i++) {
        const Item& temp = slots.at(i);
        addSpeed += temp.getSpeed();
    }
    addSpeed += this->weapon.getSpeed();

    if(this->weapon.hasSpeedOil()) addSpeed += 1;

    return addSpeed;
}

void Inventory::equipWeapon(const Item& newWeapon) {
    //remove o oleo antes de equipar a nova arma
    this->weapon.setOil(0);
    this->weapon = newWeapon;
}