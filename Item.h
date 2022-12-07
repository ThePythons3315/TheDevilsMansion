#pragma once

#include <iostream>
#include <string>
#include "GameUI.h"

class Item
{
private:
	std::string name;
	std::string description;
	int healing;
	int statusEffect;
public:
	// Constructors
	Item();
	Item(std::string _name, std::string _description, int _healing, int _statusEffect);

	// Mutator Functions -- Functions that will be allowed to change private variables
	void setName(std::string _name);
	void setDescritpion(std::string _description);
	void setHealing(int _healing);
	void setStatusEffect(int _statusEffect); // 0 for no status effect, 1 for paralysis, 2 for burn

	// Accessor Functions -- Functions that will return values of private functions
	std::string getName();
	std::string getDescription();
	int getHealing();
	int getStatusEffect();

	// Shows the items attributes
	void viewItemDescription(GameUI console);
};