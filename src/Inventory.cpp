#include "Inventory.h"
#include <iostream>

Inventory::Inventory(std::vector<Item> slots, unsigned int slotsSize, Item* bag, Item* weapon) : slots(slots), slotsSize(slotsSize), bag(bag), weapon(weapon) {}

bool Inventory::isFull() {
    return slots.size() == slotsSize;
}

void Inventory::printInventory() {
    for(int i = 0; i < slots.size(); i++) {
        std::cout << printItem() << std::endl;
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