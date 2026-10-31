#include "../include/Player.h"
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

    // Instancia e equipa a arma inicial "Graveto" diretamente na variável isolada
    Item graveto(0, "Graveto", "Common", 0, 1, 0, 0);
    this->equippedWeapon = graveto;
    this->hasWeaponEquipped = true;

    ajustarVida(currentLife);
}

Player::~Player() {}

// ---------------- Inventário ----------------

const Inventory& Player::getInventory() const { return inventory; }

void Player::setInventory(const Inventory& novo) {
    inventory = novo;
    ajustarVida(currentLife);
}

bool Player::addItem(const Item& item) {
    if (!inventory.addItem(item)) return false;
    ajustarVida(static_cast<long long>(currentLife) + item.getLife());
    return true;
}

bool Player::removeItem(int index) {
    if (!inventory.removeItem(index)) return false;
    ajustarVida(currentLife);
    return true;
}

bool Player::replaceItem(int index, const Item& novo) {
    Item antigo;
    if (!inventory.replaceItem(index, novo, &antigo)) return false;

    int vidaNova = novo.getLife();
    int vidaVelha = antigo.getLife();
    long long vidaAtual = currentLife;
    if (vidaNova > vidaVelha) {
        vidaAtual += static_cast<long long>(vidaNova) - vidaVelha;
    }
    ajustarVida(vidaAtual);
    return true;
}

const Item* Player::getItem(int index) const { return inventory.getItem(index); }

// ---------------- Arma Equipada ----------------

const Item* Player::getWeapon() const {
    return hasWeaponEquipped ? &equippedWeapon : nullptr;
}

Item* Player::getWeapon() {
    return hasWeaponEquipped ? &equippedWeapon : nullptr;
}

bool Player::equipWeaponFromSlot(int slotIndex) {
    Item novaArma;
    
    // 1. Remove a nova arma da mochila
    if (!inventory.removeItem(slotIndex, &novaArma)) {
        return false;
    }

    // 2. Se já havia uma arma equipada, ela é descartada/substituída pela nova
    // (A arma antiga é sobrescrita e não retorna para o inventário)
    equippedWeapon = novaArma;
    hasWeaponEquipped = true;

    // 3. Atualiza os atributos de vida do jogador com a nova arma
    ajustarVida(currentLife);
    
    std::cout << ">> " << novaArma.getName() << " foi equipada! A arma anterior foi descartada.\n";
    return true;
}

bool Player::applyWeaponOil(int option) {
    return hasWeaponEquipped && equippedWeapon.applyOil(option);
}

// ---------------- Atributos Totais ----------------

int Player::getTotalMaxLife() const {
    long long total = static_cast<long long>(maxLife) + inventory.getBonusLife();
    if (hasWeaponEquipped) total += equippedWeapon.getLife();
    return static_cast<int>(std::max(1LL, std::min(total, static_cast<long long>(INT_MAX))));
}

int Player::getTotalAttack() const {
    long long total = static_cast<long long>(attack) + inventory.getAttack();
    if (hasWeaponEquipped) total += equippedWeapon.getAttack();
    return static_cast<int>(std::max(0LL, std::min(total, static_cast<long long>(INT_MAX))));
}

int Player::getTotalArmor() const {
    long long total = static_cast<long long>(armor) + inventory.getArmor();
    if (hasWeaponEquipped) total += equippedWeapon.getArmor();
    return static_cast<int>(std::max(0LL, std::min(total, static_cast<long long>(INT_MAX))));
}

int Player::getTotalSpeed() const {
    long long total = static_cast<long long>(speed) + inventory.getSpeed();
    if (hasWeaponEquipped) total += equippedWeapon.getSpeed();
    return static_cast<int>(std::max(0LL, std::min(total, static_cast<long long>(INT_MAX))));
}

void Player::ajustarVida(long long vida) {
    currentLife = static_cast<int>(std::max(0LL, std::min(vida, static_cast<long long>(getTotalMaxLife()))));
}

void Player::heal(int quantidade) {
    if (quantidade <= 0) return;
    ajustarVida(static_cast<long long>(currentLife) + quantidade);
}

void Player::fullHeal() { ajustarVida(getTotalMaxLife()); }

void Player::printStats() {
    std::cout << " Player: " << getName() << std::endl;
    std::cout << "| Moedas: " << getCoins() << std::endl;
    std::cout << "| Vida Maxima: " << getMaxLife() << " | Total: " << getTotalMaxLife() << std::endl;
    std::cout << "| Vida Atual: " << getCurrentLife() << " | Maximo: " << getTotalMaxLife() << std::endl;
    std::cout << "| Ataque: " << getAttack() << " | Total: " << getTotalAttack() << std::endl;
    std::cout << "| Armadura: " << getArmor() << " | Total: " << getTotalArmor() << std::endl;
    std::cout << "| Velocidade: " << getSpeed() << " | Total: " << getTotalSpeed() << std::endl;
}

void Player::printInventory() { inventory.printInventory(getWeapon()); }

int Player::getCoins() const { return coins; }
void Player::setCoins(int valor) {
    if (valor < 0) throw std::invalid_argument("O saldo de moedas nao pode ser negativo.");
    coins = valor;
}

void Player::addCoins(int valor) {
    if (valor < 0) throw std::invalid_argument("A quantidade de moedas adicionada nao pode ser negativa.");
    if (valor > INT_MAX - coins) throw std::overflow_error("O saldo de moedas excede o limite suportado.");
    coins += valor;
}

bool Player::spendCoins(int valor) {
    if (valor <= 0 || coins < valor) return false;
    coins -= valor;
    return true;
}

std::string Player::getName() const { return name; }
void Player::setCurrentLife(int valor) { ajustarVida(valor); }
void Player::addMaxLife(int val) {
    if (val == 0) return;
    maxLife = static_cast<int>(std::max(1LL, std::min(static_cast<long long>(maxLife) + val, static_cast<long long>(INT_MAX))));
    ajustarVida(currentLife);
}
void Player::addAttack(int val) { attack += val; }
void Player::addArmor(int val) { armor += val; }
void Player::addSpeed(int val) { speed += val; }