#pragma once
#ifndef PLAYER_H
#define PLAYER_H

#include <iostream>
#include <string>
#include "Inventory.h"
using namespace std;

class Player {
private:
	string name;
	Inventory inventory;
	int health;
public:
	// Constructors
	Player();
	Player(string, Inventory, int);

	// Mutator Functions -- Functions that will be allowed to change private variables
	void setName(string);
	void setInventory(Inventory);
	void setPlayerHealth(int);

	// Accessor Functions -- Functions that will return values of private functions
	string getName();
	Inventory getInventory();
	int getPlayerHealth();
};
#endif // !PLAYER_H