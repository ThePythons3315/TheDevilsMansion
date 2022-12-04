#pragma once

#include <iostream>
#include <string>

class Item
{
private:
	std::string name;
	int healing;
public:
	// Constructors
	Item();
	Item(std::string _name, int _healing);

	// Mutator Functions -- Functions that will be allowed to change private variables
	void setName(std::string _name);
	void setHealing(int _healing);

	// Accessor Functions -- Functions that will return values of private functions
	std::string getName();
	int getHealing();
};