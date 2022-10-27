#include "Player.h"
#include <string.h>
using namespace std;

// Constructors
Player::Player() {
	name = "";
	inventory;
	health = 100;
};
Player::Player(string n, Inventory invent, int playerHealth) {
	name = n;
	inventory = invent;
	health = playerHealth;
}

// Mutator Functions -- Functions that will be allowed to change private variables
void Player::setName(string n) {
	name = n;
}
void Player::setInventory(Inventory invent) {
	inventory = invent;
}
void Player::setPlayerHealth(int playerHealth) {
	health = playerHealth;
}

// Accessor Functions -- Functions that will return values of private functions
string Player::getName() {
	return name;
}
Inventory Player::getInventory() {
	return inventory;
}
int Player::getPlayerHealth() {
	return health;
}