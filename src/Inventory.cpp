#include "../include/Inventory.h"
#include "../include/GameItemException.h"
#include <algorithm>
#include <iostream>
#include <limits>
#include <stdexcept>

namespace {

template <typename Getter>
int somarBonus(const std::vector<Item>& slots, Getter getter) {
    long long total = 0;
    for (const Item& item : slots) {
        total += getter(item);
    }
    return static_cast<int>(std::max(
        static_cast<long long>(std::numeric_limits<int>::min()),
        std::min(total, static_cast<long long>(std::numeric_limits<int>::max()))));
}

}

Inventory::Inventory(std::vector<Item> slots, int slotsSize)
    : slots(slots), slotsSize(slotsSize), weaponSlotIndex(-1) {
    if (slotsSize < 0 || slots.size() > static_cast<std::size_t>(slotsSize)) {
        throw std::invalid_argument("A capacidade do inventario deve ser nao negativa e comportar os itens.");
    }
}

// ----- Capacidade -----

int Inventory::getMaxSlots() const {
    return slotsSize;
}

bool Inventory::setMaxSlots(int novoTamanho) {
    if (novoTamanho < 0 || static_cast<std::size_t>(novoTamanho) < slots.size()) {
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
    return true;
}

bool Inventory::removeItem(int index, Item* removido) {
    if (index < 0 || static_cast<std::size_t>(index) >= slots.size()) {
        return false;
    }
    if (weaponSlotIndex == index) {
        slots[index].clearOils();
        weaponSlotIndex = -1;
    } else if (weaponSlotIndex > index) {
        weaponSlotIndex--;
    }

    if (removido != nullptr) {
        *removido = slots[index];
    }
    slots.erase(slots.begin() + index);

    return true;
}

bool Inventory::replaceItem(int index, const Item& novo, Item* antigo) {
    if (index < 0 || static_cast<std::size_t>(index) >= slots.size()) {
        return false;
    }
    if (antigo != nullptr) {
        *antigo = slots[index];
    }
    slots[index] = novo;

    if (weaponSlotIndex == index) {
        slots[index].clearOils();
    }
    return true;
}

Item* Inventory::getItem(int index) {
    if (index < 0 || static_cast<std::size_t>(index) >= slots.size()) {
        return nullptr;
    }
    return &slots[index];
}

const Item* Inventory::getItem(int index) const {
    if (index < 0 || static_cast<std::size_t>(index) >= slots.size()) {
        return nullptr;
    }
    return &slots[index];
}

// ----- Arma Atual (Weapon) -----

Item* Inventory::getWeapon() {
    return weaponSlotIndex >= 0
        ? &slots[static_cast<std::size_t>(weaponSlotIndex)]
        : nullptr;
}

const Item* Inventory::getWeapon() const {
    return weaponSlotIndex >= 0
        ? &slots[static_cast<std::size_t>(weaponSlotIndex)]
        : nullptr;
}

void Inventory::setWeapon(Item* newWeapon) {
    int novoIndice = -1;
    if (newWeapon != nullptr) {
        for (std::size_t i = 0; i < slots.size(); ++i) {
            if (&slots[i] == newWeapon) {
                novoIndice = static_cast<int>(i);
                break;
            }
        }
        if (novoIndice < 0) {
            throw GameItemException("A arma precisa pertencer ao inventario.");
        }
    }

    if (novoIndice == weaponSlotIndex) return;
    if (weaponSlotIndex >= 0) {
        slots[static_cast<std::size_t>(weaponSlotIndex)].clearOils();
    }
    weaponSlotIndex = novoIndice;
    if (weaponSlotIndex >= 0) {
        slots[static_cast<std::size_t>(weaponSlotIndex)].clearOils();
    }
}

bool Inventory::equipWeapon(int slotIndex) {
    if (slotIndex < 0 || static_cast<std::size_t>(slotIndex) >= slots.size()) {
        throw GameItemException("Indice de slot invalido para equipar arma!");
    }

    if (weaponSlotIndex == slotIndex) return true;

    if (weaponSlotIndex >= 0) {
        slots[static_cast<std::size_t>(weaponSlotIndex)].clearOils();
    }
    weaponSlotIndex = slotIndex;
    slots[static_cast<std::size_t>(weaponSlotIndex)].clearOils();

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
    return somarBonus(slots, [](const Item& item) { return item.getLife(); });
}
 
int Inventory::getAttack() const {
    return somarBonus(slots, [](const Item& item) { return item.getAttack(); });
}
 
int Inventory::getArmor() const {
    return somarBonus(slots, [](const Item& item) { return item.getArmor(); });
}
 
int Inventory::getSpeed() const {
    return somarBonus(slots, [](const Item& item) { return item.getSpeed(); });
}
