#include "Player.h"
#include "Inventory.h"
#include <algorithm>
#include <iostream>

Player::Player(std::string nome, unsigned int maxLife, unsigned int currentLife,
               unsigned int attack, unsigned int armor, unsigned int speed,
               unsigned int coins, Inventory inventory)
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

bool Player::removeItem(unsigned int index) {
    if (!inventory.removeItem(index)) {
        return false;
    }
    ajustarVida();
    return true;
}

bool Player::replaceItem(unsigned int index, const Item& novo) {
    Item antigo(0, "", "", 0, 0, 0, 0);
    if (!inventory.replaceItem(index, novo, &antigo)) {
        return false;
    }

    Item copiaNovo = novo;
    unsigned int vidaNova = static_cast<unsigned int>(std::max(0, copiaNovo.getLife()));
    unsigned int vidaVelha = static_cast<unsigned int>(std::max(0, antigo.getLife()));
    if (vidaNova > vidaVelha) {
        currentLife += (vidaNova - vidaVelha);
    }
    ajustarVida();
    return true;
}

// ---------------- Player Name ---------------------

std::string Player::getName() { return this->name; }

// ---------------- atributos totais ----------------

unsigned int Player::getTotalMaxLife() const { return this->maxLife + inventory.getBonusLife(); }
unsigned int Player::getTotalAttack() const { return this->attack + inventory.getAttack(); }
unsigned int Player::getTotalArmor() const { return this->armor + inventory.getArmor(); }
unsigned int Player::getTotalSpeed() const { return this->speed + inventory.getSpeed(); }

void Player::ajustarVida() {
    if (currentLife > getTotalMaxLife()) {
        currentLife = getTotalMaxLife();
    }
}

void Player::heal(unsigned int quantidade) {
    currentLife += quantidade;
    if (currentLife > getTotalMaxLife()) {
        currentLife = getTotalMaxLife();
    }
}

void Player::fullHeal() {
    currentLife = getTotalMaxLife();
}

void Player::printStats() {
    std::cout << " Player " << std::endl;
    std::cout << "| Vida Maxima: " << getMaxLife() << " | Total: " << getTotalMaxLife() << std::endl;
    std::cout << "| Vida Atual: " << getCurrentLife() << " | Maximo: " << getTotalMaxLife() << std::endl;
    std::cout << "| Ataque: " << getAttack() << " | Total: " << getTotalAttack() << std::endl;
    std::cout << "| Armadura: " << getArmor() << " | Total: " << getTotalArmor() << std::endl;
    std::cout << "| Velocidade: " << getSpeed() << " | Total: " << getTotalSpeed() << std::endl;
}

void Player::printInventory() {
    std::cout << "Inventario (" << inventory.getItemCount() << "/" << inventory.getMaxSlots() << ")\n";
    for (unsigned int i = 0; i < inventory.getItemCount(); ++i) {
        Item* temp = inventory.getItem(i);
        if (temp == nullptr) {
            continue;
        }
        std::cout << " [" << i + 1 << "] NAME = " << temp->getName()
                  << " | VIDA +" << temp->getLife() << " | ATK +" << temp->getAttack()
                  << " | ARM +" << temp->getArmor() << " | SPD +" << temp->getSpeed() << "\n";
    }
}

// ---------------- moedas ----------------

unsigned int Player::getCoins() const { return coins; }
void Player::setCoins(unsigned int valor) { coins = valor; }