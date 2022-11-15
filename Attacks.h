#pragma once

#include <iostream>
#include <string>
#include <vector>
#include "Weapon.h"

class Attacks 
{
private:
	vector<Weapon> attacks;
public:
	// Constructors
	Attacks();

	// Function that adds items to inventory
	void addAttack(Weapon);

	// Function to display all the items in the player inventory
	void displayattacks();

	// Function that searches for weapon and returns the weapon
	Weapon getWeapon(string);

	// Function used to get monster weapon
	Weapon getMonsterWeapon();

	// Get the number of items being stored in the inventory
	int getSize();

	// Function that returns a vector of the items in the inventory
	vector<Weapon> getAttacks();

	// Remove an item from the inventory
	void removeItem(int);
};