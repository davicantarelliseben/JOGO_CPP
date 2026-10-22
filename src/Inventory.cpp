#include <Inventory.h>
#include <iostream>

Inventory::Inventory(std::vector<Item> slots, unsigned int slotsSize, Item* bag, Item* weapon) : slots(slots), slotsSize(slotsSize), bag(bag), weapon(weapon) {}

bool Inventory::isFull() {
    return slots.size() == slotsSize;
}

void Inventory::printInventory() {
    for(int i = 0; i < slots.size(); i++) {
       // std::cout << printItem() << std::endl;
    }

}

bool Inventory::replaceItem(const Item& item) {
}

bool Inventory::addItem(const Item& item) {
    if(this->isFull()) {
        this->replaceItem(item);
        return 0;
    }
    this->slots.push_back(item);
    return 1;
}

unsigned int Inventory::getBonusLife() {
    unsigned int addLife = 0;
    for(int i = 0; i < slots.size(); i++) {
        Item temp = slots.at(i);
        addLife += temp.getLife();
    }
    return addLife;
}

unsigned int Inventory::getAttack() {
    unsigned int addAttack = 0;
    for(int i = 0; i < slots.size(); i++) {
        Item temp = slots.at(i);
        addAttack += temp.getAttack();
    }
    return addAttack;
}

unsigned int Inventory::getArmor() {
    unsigned int addArmor = 0;
    for(int i = 0; i < slots.size(); i++) {
        Item temp = slots.at(i);
        addArmor += temp.getArmor();
    }
    return addArmor;
}

unsigned int Inventory::getSpeed() {
    unsigned int addSpeed = 0;
    for(int i = 0; i < slots.size(); i++) {
        Item temp = slots.at(i);
        addSpeed += temp.getSpeed();
    }
    return addSpeed;
}