#include "Player.h"
#include <string.h>
using namespace std;

// Constructors
Player::Player() {
	name = "";
	inventory;
};
Player::Player(string n, Inventory invent) {
	name = n;
	inventory = invent;
}

// Mutator Functions -- Functions that will be allowed to change private variables
void Player::setName(string n) {
	name = n;
}
void Player::setInventory(Inventory invent) {
	inventory = invent;
}

// Accessor Functions -- Functions that will return values of private functions
string Player::getName() {
	return name;
}
Inventory Player::getInventory() {
	return inventory;
}