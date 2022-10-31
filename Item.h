#pragma once
#ifndef ITEM_H
#define ITEM_H

#include <iostream>
#include <string>
#include "Health.h"
using namespace std;

class Item {
private:
	string name;
	Health health;
public:
	// Constructors
	Item();
	Item(string, Health);

	// Mutator Functions -- Functions that will be allowed to change private variables
	void setName(string);
	void setHealth(Health);
	// Accessor Functions -- Functions that will return values of private functions
	string getName();
	Health getHealth();
};
#endif // !ITEM_H