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
public:
	// Constructors
	Player();
	Player(string, Inventory);

	// Mutator Functions -- Functions that will be allowed to change private variables
	void setName(string);
	void setInventory(Inventory);

	// Accessor Functions -- Functions that will return values of private functions
	string getName();
	Inventory getInventory();
};
#endif // !PLAYER_H