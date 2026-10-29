#pragma once
#include "Item.h"
#include <vector>

class Inventory {

    private:
        std::vector<Item> slots; // itens guardados 
        int slotsSize;           // capacidade maxima
        int weaponSlotIndex = -1; // rastreia o indice da arma para evitar ponteiro pendente
    
    public:
        Inventory(std::vector<Item> slots = {}, int slotsSize = 6);
        
        // --- Capacidade --- 
        int getMaxSlots() const;
        bool setMaxSlots(int novoTamanho);
        int getItemCount() const;
        bool isFull() const;
        bool isEmpty() const;

        // --- Colocar / tirar / trocar --- 
        bool addItem(const Item& item);
        bool removeItem(int index, Item* removido = nullptr);
        bool replaceItem(int index, const Item& novo, Item* antigo = nullptr);
        Item* getItem(int index);
        const Item* getItem(int index) const;

        const std::vector<Item>& getSlots() const { return slots; }

        // --- Arma atual (weapon) ---
        Item* getWeapon();
        const Item* getWeapon() const;
        void setWeapon(Item* newWeapon);
        bool equipWeapon(int slotIndex);

        void printInventory() const;

        // --- soma dos bonus de todos os itens ---
        int getBonusLife() const;
        int getAttack() const;
        int getArmor() const;
        int getSpeed() const;

}; 
