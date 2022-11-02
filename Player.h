#pragma once
#ifndef PLAYER_H
#define PLAYER_H

#include <iostream>
#include <string>
#include "Inventory.h"
#include "Health.h"
#include "Attacks.h"
using namespace std;

class Player {
private:
	string name;
	Inventory inventory;
	Attacks attacks;
	Health health;
public:
	// Constructors
	Player();
	Player(string, Inventory, Health, Attacks);

	// Mutator Functions -- Functions that will be allowed to change private variables
	void setName(string);
	void setInventory(Inventory);
	void setPlayerHealth(Health);
	void setAttacks(Attacks);

	// Accessor Functions -- Functions that will return values of private functions
	string getName();
	Inventory getInventory();
	Health getPlayerHealth();
	Attacks getAttacks();

	// For testing purposes
	void printPlayerInfo();
};
#endif // !PLAYER_H