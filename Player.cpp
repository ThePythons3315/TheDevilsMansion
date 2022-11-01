#include "Player.h"
#include <string.h>
using namespace std;

// Constructors
Player::Player() {
	name = "";
	inventory;
	health;
	weapon1;
	weapon2;
};
Player::Player(string n, Inventory invent, Health playerHealth, Weapon _weapon1, Weapon _weapon2) {
	name = n;
	inventory = invent;
	health = playerHealth;
	weapon1 = _weapon1;
	weapon2 = _weapon2;
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
void Player::setWeapon1(Weapon _weapon1) {
	weapon1 = _weapon1;
}
void Player::setWeapon2(Weapon _weapon2) {
	weapon2 = _weapon2;
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
Weapon Player::getWeapon1() {
	return weapon1;
}
Weapon Player::getWeapon2() {
	return weapon2;
}

void Player::printPlayerInfo() {
	cout << "Player Name: " << name << endl;
	cout << "Player Items: " << endl;
	inventory.displayInventory();
	cout << "Player Health: " << health.getHealth() << endl;
	cout << "Player Weapon 1: " << weapon1.getName() << endl;
	cout << "Player Weapon 2: " << weapon2.getName() << endl;
}