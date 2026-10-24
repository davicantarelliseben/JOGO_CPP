#include "Player.h"

Player::Player(int maxLife, int currentLife, int attack, int armor, int speed, unsigned int coins, Inventory inventory) : Character(maxLife, currentLife, attack, armor, speed), coins(coins), inventory(inventory) {}

Player::~Player() {}

void Player::addCoins(unsigned int amount) {
    this->coins += amount;
} 