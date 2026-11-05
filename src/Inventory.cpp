#include "../include/Inventory.h"
#include <algorithm>
#include <iostream>
#include <limits>
#include <stdexcept>

Inventory::Inventory(std::vector<Item> slots, int slotsSize)
    : slots(slots), slotsSize(slotsSize) {
    if(slotsSize < 0 || slots.size() > static_cast<std::size_t>(slotsSize)) {
        throw std::invalid_argument("A capacidade do inventario deve ser nao negativa.");
    }
}

int Inventory::getMaxSlots() const { return slotsSize; }

bool Inventory::setMaxSlots(int novoTamanho) {
    if(novoTamanho < 0 || static_cast<std::size_t>(novoTamanho) < slots.size()) return false;
    slotsSize = novoTamanho;
    return true;
}

int Inventory::getItemCount() const { return slots.size(); }
bool Inventory::isFull() const { return slots.size() >= static_cast<std::size_t>(slotsSize); }
bool Inventory::isEmpty() const { return slots.empty(); }

bool Inventory::addItem(const Item& item, Item* substituido) {
    if (!isFull()) {
        slots.push_back(item);
        return true;
    }

    std::cout << "\n\033[1;33mMochila cheia! (" << slots.size() << "/" << slotsSize << ")\033[0m\n";
    std::cout << "Item recebido: ";
    item.printItem();
    std::cout << "\nEscolha um item para substituir ou [0] para descurtar o item novo:\n";

    for (std::size_t i = 0; i < slots.size(); ++i) {
        std::cout << " [" << i + 1 << "] ";
        slots[i].printItem();
    }

    int escolha = -1;
    std::cout << "\nDigite o numero da sua escolha: ";
    if (!(std::cin >> escolha)) { //caso digite algo diferente de um numero
        std::cin.clear();
        std::cin.ignore(10000, '\n');
        std::cout << "Entrada invalida. O item novo foi descartado.\n";
        return false;
    }

    if (escolha <= 0 || escolha > static_cast<int>(slots.size())) {
        std::cout << "Voce optou por descartar o item novo.\n";
        return false;
    }

    int indexParaSubstituir = escolha - 1;
    return replaceItem(indexParaSubstituir, item, substituido);
}

bool Inventory::replaceItem(int index, const Item& novo, Item* antigo) {
    if(index < 0 || static_cast<std::size_t>(index) >= slots.size()) return false;
    if(antigo != nullptr) *antigo = slots[index];
    std::cout << "Você trocou [" << slots[index].getName() << "] por [" << novo.getName() << "]." << std::endl;
    slots[index] = novo;
    return true;
}

bool Inventory::removeItem(int index, Item* removido) {
    if(index < 0 || static_cast<std::size_t>(index) >= slots.size()) return false;
    if(removido != nullptr) *removido = slots[index];
    slots.erase(slots.begin() + index);
    return true;
}

const Item* Inventory::getItem(int index) const {
    if(index < 0 || static_cast<std::size_t>(index) >= slots.size()) return nullptr;
    return &slots[index];
}

void Inventory::printInventory(const Item* equippedWeapon) const {
    int count = slots.size();
    std::cout << "Mochila (" << count << "/" << slotsSize << ")\n";
    
    if(equippedWeapon != nullptr) {
        equippedWeapon->printItem();
    } else {
        std::cout << "| Arma Equipada: \033[90mNenhuma\033[0m\n";
    }

    for (int i = 0; i < count; ++i) {
    std::cout << " [" << i + 1 << "] ";
    slots[i].printItem();
}
}

namespace { //usando namaspace anonimo pra não sair do escopo da classe, função auxiliar para outras dentro da classe 
template <typename Getter>
int somarBonus(const std::vector<Item>& slots, Getter getter) {
    int total = 0;
    for (const Item& item : slots) {
        total += getter(item);
    }
    return total;
}
}

int Inventory::getBonusLife() const { return somarBonus(slots, [](const Item& item) { return item.getLife(); }); }
int Inventory::getAttack() const { return somarBonus(slots, [](const Item& item) { return item.getAttack(); }); }
int Inventory::getArmor() const { return somarBonus(slots, [](const Item& item) { return item.getArmor(); }); }
int Inventory::getSpeed() const { return somarBonus(slots, [](const Item& item) { return item.getSpeed(); }); }