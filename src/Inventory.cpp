#include "Inventory.h"
#include "GameItemException.h"
#include <iostream>

Inventory::Inventory(std::vector<Item> slots, int slotsSize, Item* bag, Item* weapon)
    : slots(slots), slotsSize(slotsSize), bag(bag), weapon(weapon), weaponSlotIndex(-1) {
    if (weapon != nullptr) {
        int count = slots.size();
        for (int i = 0; i < count; ++i) {
            if (&slots[i] == weapon) {
                weaponSlotIndex = i;
                break;
            }
        }
    }
}

// ----- Capacidade -----

int Inventory::getMaxSlots() const {
    return slotsSize;
}

bool Inventory::setMaxSlots(int novoTamanho) {
    int count = slots.size();
    if (novoTamanho < count) {
        return false;
    }
    slotsSize = novoTamanho;
    return true;
}

int Inventory::getItemCount() const {
    return slots.size();
}

bool Inventory::isFull() const {
    int count = slots.size();
    return count >= slotsSize;
}

bool Inventory::isEmpty() const {
    return slots.empty();
}

// ----- colocar / tirar / trocar -----

bool Inventory::addItem(const Item& item) {
    if (isFull()) {
        return false;
    }
    slots.push_back(item);
    int count = slots.size();
    if (weaponSlotIndex >= 0 && weaponSlotIndex < count) {
        weapon = &slots[weaponSlotIndex];
    }
    return true;
}

bool Inventory::removeItem(int index, Item* removido) {
    int count = slots.size();
    if (index < 0 || index >= count) {
        return false;
    }
    if (weaponSlotIndex == index) {
        if (weapon != nullptr) weapon->clearOils();
        weapon = nullptr;
        weaponSlotIndex = -1;
    } else if (weaponSlotIndex > index) {
        weaponSlotIndex--;
    }

    if (removido != nullptr) {
        *removido = slots[index];
    }
    slots.erase(slots.begin() + index);

    count = slots.size();
    if (weaponSlotIndex >= 0 && weaponSlotIndex < count) {
        weapon = &slots[weaponSlotIndex];
    }
    return true;
}

bool Inventory::replaceItem(int index, const Item& novo, Item* antigo) {
    int count = slots.size();
    if (index < 0 || index >= count) {
        return false;
    }
    if (antigo != nullptr) {
        *antigo = slots[index];
    }
    slots[index] = novo;

    if (weaponSlotIndex == index) {
        slots[index].clearOils();
        weapon = &slots[index];
    }
    return true;
}

Item* Inventory::getItem(int index) {
    int count = slots.size();
    if (index < 0 || index >= count) {
        return nullptr;
    }
    return &slots[index];
}

const Item* Inventory::getItem(int index) const {
    int count = slots.size();
    if (index < 0 || index >= count) {
        return nullptr;
    }
    return &slots[index];
}

// ----- Arma Atual (Weapon) -----

Item* Inventory::getWeapon() {
    int count = slots.size();
    if (weaponSlotIndex >= 0 && weaponSlotIndex < count) {
        weapon = &slots[weaponSlotIndex];
    }
    return weapon;
}

const Item* Inventory::getWeapon() const {
    int count = slots.size();
    if (weaponSlotIndex >= 0 && weaponSlotIndex < count) {
        return &slots[weaponSlotIndex];
    }
    return weapon;
}

void Inventory::setWeapon(Item* newWeapon) {
    if (this->weapon != nullptr && this->weapon != newWeapon) {
        this->weapon->clearOils();
    }

    this->weapon = newWeapon;
    this->weaponSlotIndex = -1;

    if (this->weapon != nullptr) {
        this->weapon->clearOils();
        int count = slots.size();
        for (int i = 0; i < count; ++i) {
            if (&slots[i] == newWeapon) {
                this->weaponSlotIndex = i;
                break;
            }
        }
    }
}

bool Inventory::equipWeapon(int slotIndex) {
    int count = slots.size();
    if (slotIndex < 0 || slotIndex >= count) {
        throw GameItemException("Indice de slot invalido para equipar arma!");
    }

    if (weaponSlotIndex >= 0 && weaponSlotIndex < count) {
        slots[weaponSlotIndex].clearOils();
    } else if (weapon != nullptr) {
        weapon->clearOils();
    }

    weaponSlotIndex = slotIndex;
    weapon = &slots[slotIndex];
    weapon->clearOils();

    return true;
}

void Inventory::printInventory() const {
    int count = slots.size();
    std::cout << "Inventario (" << count << "/" << slotsSize << ")\n";
    for (int i = 0; i < count; ++i) {
        Item temp = slots[i];
        bool isCurrentWeapon = (weaponSlotIndex == i);
        std::cout << " [" << i + 1 << "] " << temp.getName()
                  << " [" << temp.getRarity() << "]"
                  << (isCurrentWeapon ? " [ARMA ATUAL]" : "")
                  << " | VIDA " << (temp.getLife() >= 0 ? "+" : "") << temp.getLife()
                  << " | ATK "  << (temp.getAttack() >= 0 ? "+" : "") << temp.getAttack()
                  << " | ARM "  << (temp.getArmor() >= 0 ? "+" : "") << temp.getArmor()
                  << " | SPD "  << (temp.getSpeed() >= 0 ? "+" : "") << temp.getSpeed();
        if (temp.hasAttackOil() || temp.hasArmorOil() || temp.hasSpeedOil()) {
            std::cout << " (Oleos:";
            if (temp.hasAttackOil()) std::cout << " Ataque";
            if (temp.hasArmorOil())  std::cout << " Armadura";
            if (temp.hasSpeedOil())  std::cout << " Velocidade";
            std::cout << ")";
        }
        std::cout << "\n";
    }
}

// ---------------- bonus ----------------
 
int Inventory::getBonusLife() const {
    int total = 0;
    for (const Item& temp : slots) {
        total += temp.getLife();
    }
    return total;
}
 
int Inventory::getAttack() const {
    int total = 0;
    for (const Item& temp : slots) { 
        total += temp.getAttack();
    }
    return total;
}
 
int Inventory::getArmor() const {
    int total = 0;
    for (const Item& temp : slots) {
        total += temp.getArmor();
    }
    return total;
}
 
int Inventory::getSpeed() const {
    int total = 0;
    for (const Item& temp : slots) { 
        total += temp.getSpeed();
    }
    return total;
}
