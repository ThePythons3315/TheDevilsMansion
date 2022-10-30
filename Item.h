#pragma once
#ifndef ITEM_H
#define ITEM_H

#include <iostream>
#include <string>
using namespace std;

class Item {
private:
	string name;
	int health;
public:
	// Constructors
	Item();
	Item(string, int);

	// Mutator Functions -- Functions that will be allowed to change private variables
	void setName(string);
	void setHealth(int);
	// Accessor Functions -- Functions that will return values of private functions
	string getName();
	int getHealth();
};
#endif // !ITEM_H