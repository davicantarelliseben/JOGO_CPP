#include "include/Inventory.h"
#include <iostream>

Inventory::Inventory(std::vector<Item> slots, unsigned int slotsSize, Item* bag, Item* weapon) : slots(slots) , slotsSize(slotsSize), bag(bag), weapon(weapon) {}

// ----- Capacidade -----

unsigned int Inventory::getMaxSlots() const {
    return slotsSize;
}

bool Inventory::setMaxSlots(unsigned int novoTamanho) {
    if(novoTamanho < slots.size()) {
        return false; //não deixa diminuir e "sumir" com itens
    }
    slotsSize = novoTamanho;
    return true;
}

unsigned int Inventory::getItemCount() const {
    return slots.size();
}

bool Inventory::isFull() const {
    return slots.size() >= slotsSize;
}

// ----- colocar / tirar / trocar -----

bool Inventory::addItem(const Item& item){
    if(isFull()) {
        return false; //quem chamou decide  : descartar ou usar replaceItem
    }
    slots.push_back(item);
    return true;
}

bool Inventory::removeItem(unsigned int index, Item* removido){
    if(index >= slots.size()){
        return false;
    }
    if(removido != nullptr){
        *removido = slots[index]; //remove o item tirado, se quiser usar (ex : vender)
    }
    slots.erase(slots.begin() + index);
    return true;
}

bool Inventory::replaceItem(unsigned int index, const Item& novo, Item* antigo){
    if(index >= slots.size()){
        return false;
    }
    if(antigo != nullptr) {
        *antigo = slots[index];
    }
    slots[index] = novo;
    return true;
}

Item* Inventory::getItem(unsigned int index) {
    if(index >= slots.size()){
        return nullptr;
    }
    return &slots[index];
}

void Inventory::printInventory() const {
    std::cout << "Inventario (" << slots.size() << "/" << slotsSize << ")\n";
    for (unsigned int i = 0; i < slots.size(); i++) {
        Item temp = slots[i];
        std::cout << " [" << i + 1 << "] " << "NAME = "<< temp.getName() << " | VIDA +" << temp.getLife() << " | ATK +" << temp.getAttack() << " | ARM +" << temp.getArmor() << " | SPD +" << temp.getSpeed() << "\n";

    }
}

// ---------------- bonus ----------------
 
unsigned int Inventory::getBonusLife() const {
    unsigned int total = 0;
    for (Item temp : slots){
        total += temp.getLife();
    }
    return total;
}
 
unsigned int Inventory::getAttack() const {
    unsigned int total = 0;
    for (Item temp : slots){ 
        total += temp.getAttack();
    }
        return total;
}
 
unsigned int Inventory::getArmor() const {
    unsigned int total = 0;
    for (Item temp : slots){
        total += temp.getArmor();
    }
    return total;
}
 
unsigned int Inventory::getSpeed() const {
    unsigned int total = 0;
    for (Item temp : slots){ 
        total += temp.getSpeed();
    }
    return total;
}