#ifndef PLAYER_H
#define PLAYER_H

#include "Character.h"
#include "Inventory.h"

class Player : public Character {
private:
    std::string name;
    unsigned int coins;
    Inventory inventory;

    void ajustarVida();   // garante que a vida atual nao passe do maximo total

public:
    Player(std::string nome,unsigned int maxLife, unsigned int currentLife, unsigned int attack, unsigned int armor, unsigned int speed, unsigned int coins, Inventory inventory);
    ~Player();

    // --- inventario ---
    const Inventory& getInventory() const;        // so leitura
    void setInventory(const Inventory& novo);
    bool addItem(const Item& item);
    bool removeItem(unsigned int index);
    bool replaceItem(unsigned int index, const Item& novo);

    // --- Player nome ---
    std::string getName();
    // --- atributos totais (base + itens) ---
    unsigned int getTotalMaxLife() const;
    unsigned int getTotalAttack() const;
    unsigned int getTotalArmor() const;
    unsigned int getTotalSpeed() const;

    void heal(unsigned int quantidade);
    void fullHeal();

    void printStats();
    void printInventory();

    unsigned int getCoins() const;
    void setCoins(unsigned int valor);
};

#endif