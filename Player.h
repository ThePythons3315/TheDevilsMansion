#pragma once
#ifndef PLAYER_H
#define PLAYER_H

#include <iostream>
#include <string>
#include "Inventory.h"
#include "Health.h"
using namespace std;

class Player {
private:
	string name;
	Inventory inventory;
	Health health;
public:
	// Constructors
	Player();
	Player(string, Inventory, Health);

	// Mutator Functions -- Functions that will be allowed to change private variables
	void setName(string);
	void setInventory(Inventory);
	void setPlayerHealth(Health);

	// Accessor Functions -- Functions that will return values of private functions
	string getName();
	Inventory getInventory();
	Health getPlayerHealth();
};
#endif // !PLAYER_H