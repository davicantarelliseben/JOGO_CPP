#pragma once
#include "Character.h"
#include "Inventory.h"
#include "Item.h"
#include <string>

class Player : public Character {
private:
    std::string name;
    int coins;
    Inventory inventory;
    
    Item equippedWeapon;
    bool hasWeaponEquipped = false;

    void ajustarVida(long long vida);

public:
    Player(std::string nome, int maxLife, int currentLife,
           int attack, int armor, int speed,
           int coins, Inventory inventory);
    virtual ~Player();

    // Inventário / Mochila
    const Inventory& getInventory() const;
    void setInventory(const Inventory& novo);
    bool addItem(const Item& item);
    bool removeItem(int index);
    bool replaceItem(int index, const Item& novo);
    const Item* getItem(int index) const;

    // Gestão da Arma Equipada Isolada
    const Item* getWeapon() const;
    Item* getWeapon();
    bool hasWeapon() const { return hasWeaponEquipped; }
    bool equipWeaponFromSlot(int slotIndex);
    bool unequipWeapon();
    bool applyWeaponOil(int option);

    // Getters de Atributos Totais (Base + Equipamentos/Inventário)
    int getTotalMaxLife() const;
    int getTotalAttack() const;
    int getTotalArmor() const;
    int getTotalSpeed() const;

    // Sobrescrevendo os métodos da classe Character para retornar os valores totais
    int getMaxLife() const override { return getTotalMaxLife(); }
    int getAttack() const override { return getTotalAttack(); }
    int getArmor() const override { return getTotalArmor(); }
    int getSpeed() const override { return getTotalSpeed(); }

    std::string getName() const;
    int getCoins() const;
    void setCoins(int valor);
    void addCoins(int valor);
    bool spendCoins(int valor);

    void heal(int quantidade);
    void fullHeal();
    void setCurrentLife(int valor) override;
    void addMaxLife(int val);
    void addAttack(int val);
    void addArmor(int val);
    void addSpeed(int val);

    void printStats();
    void printInventory();
};