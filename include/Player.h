#ifndef PLAYER_H
#define PLAYER_H

#include "Character.h"
#include "Inventory.h"
#include <string>

class Player : public Character {
private:
    std::string name;
    int coins;
    Inventory inventory;

    void ajustarVida(long long vida);

public:
    Player(std::string nome, int maxLife, int currentLife, int attack, int armor, int speed, int coins, Inventory inventory);
    ~Player() override;

    // --- inventario ---
    const Inventory& getInventory() const;
    void setInventory(const Inventory& novo);
    bool addItem(const Item& item);
    bool removeItem(int index);
    bool replaceItem(int index, const Item& novo);
    const Item* getItem(int index) const;

    // --- arma atual ---
    const Item* getWeapon() const;
    bool applyWeaponOil(int option);
    void setWeapon(Item* w);
    bool equipWeapon(int slotIndex);

    // --- Player nome ---
    std::string getName() const;
    // --- atributos totais (base + itens) ---
    int getTotalMaxLife() const;
    int getTotalAttack() const;
    int getTotalArmor() const;
    int getTotalSpeed() const;

    void heal(int quantidade);
    void fullHeal();

    void printStats();
    void printInventory();

    // --- moedas ---
    int getCoins() const;
    void setCoins(int valor);
    void addCoins(int valor);
    bool spendCoins(int valor);

    // --- incrementos nos atributos base ---
    void setCurrentLife(int valor);
    void addMaxLife(int val);
    void addAttack(int val);
    void addArmor(int val);
    void addSpeed(int val);
};

#endif
