#pragma once
#include "Item.h"
#include <vector>

class Inventory {
private:
    std::vector<Item> slots;
    int slotsSize;

public:
    Inventory(std::vector<Item> slots = {}, int slotsSize = 6);

    int getMaxSlots() const;
    bool setMaxSlots(int novoTamanho);
    int getItemCount() const;
    bool isFull() const;
    bool isEmpty() const;

    bool addItem(const Item& item);
    bool removeItem(int index, Item* removido = nullptr);
    bool replaceItem(int index, const Item& novo, Item* antigo = nullptr);
    const Item* getItem(int index) const;

    void printInventory(const Item* equippedWeapon = nullptr) const;

    // Bónus apenas dos itens guardados no inventário/mochila
    int getBonusLife() const;
    int getAttack() const;
    int getArmor() const;
    int getSpeed() const;
};