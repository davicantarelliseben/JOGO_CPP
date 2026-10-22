#include <Player.h>

Player::Player(unsigned int maxLife, unsigned int currentLife, unsigned int attack, unsigned int armor, unsigned int speed, unsigned int coins, Inventory inventory) : Character(maxLife, currentLife, attack, armor, speed), coins(coins), inventory(inventory) {}

Player::~Player() {}

