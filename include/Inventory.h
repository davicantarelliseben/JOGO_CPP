#pragma once
#include "Item.h"
#include <vector>

class Inventory {

    private:
        std::vector<Item> slots; // itens  guardados 
        unsigned int slotsSize;  // capacidade maxima
        Item* bag;
        Item* weapon;
    
    public:
        Inventory(std::vector<Item> slots, unsigned int slotsSize, Item* bag, Item* weapon);
        
        // --- Capacidade --- 
        unsigned int getMaxSlots() const; //Retorna a quantidade maxima de slots do inventario
        bool setMaxSlots(unsigned int novoTamanho); //Modificador da quantidade maxima de slots no inventario
        unsigned int getItemCount() const; // retorna a quantidade de itens na bolsa
        bool isFull() const; //Retorna se o inventário está cheio ou não
        bool isEmpty() const; //Retorna se o inventário está vazio ou não

        // --- Colocar / tirar / trocar --- 
        bool addItem(const Item& item); // Adiciona um item ao inventário
        bool removeItem(unsigned int index, Item* removido = nullptr); //remove um item usando numeros já previamente setados usando um indice
        bool replaceItem(unsigned int index, const Item& novo, Item* antigo = nullptr); //Troca um item por outro
        Item* getItem(unsigned int index); //Retorna o item usando um indice

        void printInventory() const;// Printa na tela o inventário

        // --- soma dos bonus de todos os itens ---
        unsigned int getBonusLife() const; //Retorna a vida Bonus que é adicionada
        unsigned int getAttack() const; // Retorna o ataque bonus que é adicionada
        unsigned int getArmor() const; // Retorna a armadura bonus que é adicionada
        unsigned int getSpeed() const; // Retorna a velocidade bonus que é adicionada

}; 