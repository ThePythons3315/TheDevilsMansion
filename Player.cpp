#include "Player.h"
#include <string.h>
using namespace std;

// Constructors
Player::Player()
{
	name = "";
	inventory;
	health;
	attacks;
};
Player::Player(string _name, Inventory _inventory, Health _health, Attacks _attacks)
{
	name = _name;
	inventory = _inventory;
	health = _health;
	attacks = _attacks;
}

// Mutator Functions -- Functions that will be allowed to change private variables
void Player::setName(string _name)
{
	name = _name;
}
void Player::setInventory(Inventory _inventory)
{
	inventory = _inventory;
}
void Player::setPlayerHealth(Health _health)
{
	health = _health;
}
void Player::setAttacks(Attacks _attacks)
{
	attacks = _attacks;
}

// Accessor Functions -- Functions that will return values of private functions
string Player::getName()
{
	return name;
}
Inventory Player::getInventory()
{
	return inventory;
}
Health Player::getPlayerHealth()
{
	return health;
}
Attacks Player::getAttacks()
{
	return attacks;
}

void Player::printPlayerInfo() {
	cout << "Player Name: " << name << endl;
	//cout << "Player Items: " << endl;
	inventory.displayPlayerInventory();
	cout << "Player Health: " << health.getHealth() << endl;
	attacks.displayattacks();
}