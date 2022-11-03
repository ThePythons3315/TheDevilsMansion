#include "Player.h"
#include <string.h>
using namespace std;

// Constructors
Player::Player() {
	name = "";
	inventory;
	health;
	attacks;
};
Player::Player(string n, Inventory invent, Health playerHealth, Attacks _attacks) {
	name = n;
	inventory = invent;
	health = playerHealth;
	attacks = _attacks;
}

// Mutator Functions -- Functions that will be allowed to change private variables
void Player::setName(string n) {
	name = n;
}
void Player::setInventory(Inventory invent) {
	inventory = invent;
}
void Player::setPlayerHealth(Health playerHealth) {
	health = playerHealth;
}
void Player::setAttacks(Attacks _attacks) {
	attacks = _attacks;
}


// Accessor Functions -- Functions that will return values of private functions
string Player::getName() {
	return name;
}
Inventory Player::getInventory() {
	return inventory;
}
Health Player::getPlayerHealth() {
	return health;
}
Attacks Player::getAttacks() {
	return attacks;
}

void Player::printPlayerInfo() {
	cout << "Player Name: " << name << endl;
	//cout << "Player Items: " << endl;
	inventory.displayPlayerInventory();
	cout << "Player Health: " << health.getHealth() << endl;
	attacks.displayattacks();
}