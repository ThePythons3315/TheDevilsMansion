#pragma once
#ifndef ITEM_H
#define ITEM_H

#include <iostream>
#include <string>
using namespace std;

class Item {
private:
	string name;
public:
	// Constructors
	Item();
	Item(string);

	// Mutator Functions -- Functions that will be allowed to change private variables
	void setName(string);

	// Accessor Functions -- Functions that will return values of private functions
	string getName();
};
#endif // !ITEM_H