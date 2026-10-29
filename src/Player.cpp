#include "Player.h"
#include "Inventory.h"
#include <algorithm>
#include <climits>
#include <iostream>
#include <stdexcept>

Player::Player(std::string nome, int maxLife, int currentLife,
               int attack, int armor, int speed,
               int coins, Inventory inventory)
    : Character(maxLife, currentLife, attack, armor, speed),
      name(nome), coins(coins), inventory(inventory) {
    if (coins < 0) {
        throw std::invalid_argument("O saldo inicial de moedas nao pode ser negativo.");
    }
    ajustarVida(currentLife);
}

Player::~Player() {}

// ---------------- inventario ----------------

const Inventory& Player::getInventory() const {
    return inventory;
}

void Player::setInventory(const Inventory& novo) {
    inventory = novo;
    ajustarVida(currentLife);
}

bool Player::addItem(const Item& item) {
    if (!inventory.addItem(item)) {
        return false;
    }

    ajustarVida(static_cast<long long>(currentLife) + item.getLife());
    return true;
}

bool Player::removeItem(int index) {
    if (!inventory.removeItem(index)) {
        return false;
    }
    ajustarVida(currentLife);
    return true;
}

bool Player::replaceItem(int index, const Item& novo) {
    Item antigo(0, "", "", 0, 0, 0, 0);
    if (!inventory.replaceItem(index, novo, &antigo)) {
        return false;
    }

    int vidaNova = novo.getLife();
    int vidaVelha = antigo.getLife();
    long long vidaAtual = currentLife;
    if (vidaNova > vidaVelha) {
        vidaAtual += static_cast<long long>(vidaNova) - vidaVelha;
    }
    ajustarVida(vidaAtual);
    return true;
}

const Item* Player::getItem(int index) const {
    return inventory.getItem(index);
}

// ---------------- arma atual ----------------

const Item* Player::getWeapon() const {
    return inventory.getWeapon();
}

bool Player::applyWeaponOil(int option) {
    Item* weapon = inventory.getWeapon();
    return weapon != nullptr && weapon->applyOil(option);
}

void Player::setWeapon(Item* w) {
    inventory.setWeapon(w);
}

bool Player::equipWeapon(int slotIndex) {
    return inventory.equipWeapon(slotIndex);
}

// ---------------- Player Name ---------------------

std::string Player::getName() const { return this->name; }

// ---------------- atributos totais ----------------

int Player::getTotalMaxLife() const {
    const long long total = static_cast<long long>(maxLife) + inventory.getBonusLife();
    return static_cast<int>(std::max(
        1LL, std::min(total, static_cast<long long>(INT_MAX))));
}

int Player::getTotalAttack() const {
    const long long total = static_cast<long long>(attack) + inventory.getAttack();
    return static_cast<int>(std::max(
        0LL, std::min(total, static_cast<long long>(INT_MAX))));
}

int Player::getTotalArmor() const {
    const long long total = static_cast<long long>(armor) + inventory.getArmor();
    return static_cast<int>(std::max(
        0LL, std::min(total, static_cast<long long>(INT_MAX))));
}

int Player::getTotalSpeed() const {
    const long long total = static_cast<long long>(speed) + inventory.getSpeed();
    return static_cast<int>(std::max(
        0LL, std::min(total, static_cast<long long>(INT_MAX))));
}

void Player::ajustarVida(long long vida) {
    currentLife = static_cast<int>(std::max(
        0LL, std::min(vida, static_cast<long long>(getTotalMaxLife()))));
}

void Player::heal(int quantidade) {
    if (quantidade <= 0) return;
    ajustarVida(static_cast<long long>(currentLife) + quantidade);
}

void Player::fullHeal() {
    ajustarVida(getTotalMaxLife());
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
void Player::setCoins(int valor) {
    if (valor < 0) {
        throw std::invalid_argument("O saldo de moedas nao pode ser negativo.");
    }
    coins = valor;
}

void Player::addCoins(int valor) {
    if (valor < 0) {
        throw std::invalid_argument("A quantidade de moedas adicionada nao pode ser negativa.");
    }
    if (valor > INT_MAX - coins) {
        throw std::overflow_error("O saldo de moedas excede o limite suportado.");
    }
    coins += valor;
}

bool Player::spendCoins(int valor) {
    if (valor <= 0 || coins < valor) return false;
    coins -= valor;
    return true;
}

// ---------------- incrementos nos atributos base ----------------

void Player::setCurrentLife(int valor) {
    ajustarVida(valor);
}

void Player::addMaxLife(int val) {
    if (val == 0) return;
    const long long novaVidaMax = static_cast<long long>(maxLife) + val;
    maxLife = static_cast<int>(std::max(1LL, std::min(
        novaVidaMax, static_cast<long long>(INT_MAX))));
    ajustarVida(currentLife);
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
