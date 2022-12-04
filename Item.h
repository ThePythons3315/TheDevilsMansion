#pragma once

#include <iostream>
#include <string>

class Item
{
private:
	std::string name;
	int healing;
	int statusEffect;
public:
	// Constructors
	Item();
	Item(std::string _name, int _healing, int _statusEffect);

	// Mutator Functions -- Functions that will be allowed to change private variables
	void setName(std::string _name);
	void setHealing(int _healing);
	void setStatusEffect(int _statusEffect); // 0 for no status effect, 1 for paralysis, 2 for burn

	// Accessor Functions -- Functions that will return values of private functions
	std::string getName();
	int getHealing();
	int getStatusEffect();
};