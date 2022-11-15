#pragma once

#include <iostream>
#include <string>

class Health
{
private:
	int health;
	int maxHealth;
public:
	// Constructors
	Health();
	Health(int, int);

	// Mutator Functions -- Functions that will be allowed to change private variables
	void setHealth(int);
	void setMaxHealth(int);
	void changeHealth(int);

	// Accessor Functions -- Functions that will return values of private functions
	int getHealth();
	int getMaxHealth();

	// Displays the current health of the creature
	void displayHealth();
};