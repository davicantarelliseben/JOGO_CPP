#include "Player.h"
#include "Inventory.h"
#include <algorithm>
#include <iostream>

Player::Player(std::string nome, int maxLife, int currentLife,
               int attack, int armor, int speed,
               int coins, Inventory inventory)
    : Character(maxLife, currentLife, attack, armor, speed),
      name(nome), coins(coins), inventory(inventory) {
    currentLife = std::min(currentLife, getTotalMaxLife());
    setCurrentLife(currentLife);
}

Player::~Player() {}

// ---------------- inventario ----------------

const Inventory& Player::getInventory() const {
    return inventory;
}

Inventory& Player::getInventory() {
    return inventory;
}

void Player::setInventory(const Inventory& novo) {
    inventory = novo;
    ajustarVida();
}

bool Player::addItem(const Item& item) {
    if (!inventory.addItem(item)) {
        return false;
    }

    Item copia = item;
    currentLife += copia.getLife();
    ajustarVida();
    return true;
}

bool Player::removeItem(int index) {
    if (!inventory.removeItem(index)) {
        return false;
    }
    ajustarVida();
    return true;
}

bool Player::replaceItem(int index, const Item& novo) {
    Item antigo(0, "", "", 0, 0, 0, 0);
    if (!inventory.replaceItem(index, novo, &antigo)) {
        return false;
    }

    Item copiaNovo = novo;
    int vidaNova = copiaNovo.getLife();
    int vidaVelha = antigo.getLife();
    if (vidaNova > vidaVelha) {
        currentLife += (vidaNova - vidaVelha);
    }
    ajustarVida();
    return true;
}

Item* Player::getItem(int index) {
    return inventory.getItem(index);
}

// ---------------- arma atual ----------------

Item* Player::getWeapon() {
    return inventory.getWeapon();
}

const Item* Player::getWeapon() const {
    return inventory.getWeapon();
}

void Player::setWeapon(Item* w) {
    inventory.setWeapon(w);
}

bool Player::equipWeapon(int slotIndex) {
    return inventory.equipWeapon(slotIndex);
}

// ---------------- Player Name ---------------------

std::string Player::getName() { return this->name; }

// ---------------- atributos totais ----------------

int Player::getTotalMaxLife() const {
    return std::max(1, this->maxLife + inventory.getBonusLife());
}

int Player::getTotalAttack() const {
    return std::max(0, this->attack + inventory.getAttack());
}

int Player::getTotalArmor() const {
    return std::max(0, this->armor + inventory.getArmor());
}

int Player::getTotalSpeed() const {
    return std::max(0, this->speed + inventory.getSpeed());
}

void Player::ajustarVida() {
    if (currentLife > getTotalMaxLife()) {
        currentLife = getTotalMaxLife();
    }
}

void Player::heal(int quantidade) {
    if (quantidade <= 0) return;
    currentLife += quantidade;
    if (currentLife > getTotalMaxLife()) {
        currentLife = getTotalMaxLife();
    }
}

void Player::fullHeal() {
    currentLife = getTotalMaxLife();
}

void Player::printStats() {
    std::cout << " Player: " << getName() << std::endl;
    std::cout << "| Moedas: " << getCoins() << std::endl;
    std::cout << "| Vida Maxima: " << getMaxLife() << " | Total: " << getTotalMaxLife() << std::endl;
    std::cout << "| Vida Atual: " << getCurrentLife() << " | Maximo: " << getTotalMaxLife() << std::endl;
    std::cout << "| Ataque: " << getAttack() << " | Total: " << getTotalAttack() << std::endl;
    std::cout << "| Armadura: " << getArmor() << " | Total: " << getTotalArmor() << std::endl;
    std::cout << "| Velocidade: " << getSpeed() << " | Total: " << getTotalSpeed() << std::endl;
    if (getWeapon() != nullptr) {
        std::cout << "| Arma Equipada: " << getWeapon()->getName() << std::endl;
    }
}

void Player::printInventory() {
    inventory.printInventory();
}

// ---------------- moedas ----------------

int Player::getCoins() const { return coins; }
void Player::setCoins(int valor) { coins = valor; }

void Player::addCoins(int valor) {
    coins += valor;
}

bool Player::spendCoins(int valor) {
    if (coins < valor) return false;
    coins -= valor;
    return true;
}

// ---------------- incrementos nos atributos base ----------------

void Player::addMaxLife(int val) {
    maxLife += val;
    heal(val);
}

void Player::addAttack(int val) {
    attack += val;
}

void Player::addArmor(int val) {
    armor += val;
}

void Player::addSpeed(int val) {
    speed += val;
}
