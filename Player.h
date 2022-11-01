#pragma once
#ifndef PLAYER_H
#define PLAYER_H

#include <iostream>
#include <string>
#include "Inventory.h"
#include "Health.h"
#include "Weapon.h"
using namespace std;

class Player {
private:
	string name;
	Inventory inventory;
	Health health;
	Weapon weapon1;
	Weapon weapon2;
public:
	// Constructors
	Player();
	Player(string, Inventory, Health, Weapon, Weapon);

	// Mutator Functions -- Functions that will be allowed to change private variables
	void setName(string);
	void setInventory(Inventory);
	void setPlayerHealth(Health);
	void setWeapon1(Weapon);
	void setWeapon2(Weapon);

	// Accessor Functions -- Functions that will return values of private functions
	string getName();
	Inventory getInventory();
	Health getPlayerHealth();
	Weapon getWeapon1();
	Weapon getWeapon2();

	// For testing purposes
	void printPlayerInfo();
};
#endif // !PLAYER_H