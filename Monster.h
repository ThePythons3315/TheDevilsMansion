#pragma once

#include <iostream>
#include <string>
#include "GameUI.h"
#include "Inventory.h"

class Monster
{
private:
	std::string name;
	std::string description;
	Inventory* inventory;
	int health;
	int maxHealth;
	bool alive;
public:
	// Constructors
	Monster();
	Monster(std::string _name, std::string _description, int _health, int _maxHealth, bool _alive);

	// Mutator Functions -- Functions that will be allowed to change private variables
	void setName(std::string _name);
	void setDescription(std::string _name);
	void setInventory(Inventory& _inventory);
	void setHealth(int _health);
	void setMaxHealth(int _maxHealth);
	void setAlive(bool _alive);

	// Accessor Functions -- Functions that will return values of private functions
	std::string getName();
	std::string getDescription();
	Inventory* getInventory();
	int getHealth();
	int getMaxHealth();
	bool getAlive();

	// Prints all of the player's attributes to the screen - mainly for testing.
	void printMonsterInfo(GameUI console);
	void printMonsterInRoom(GameUI console);

	// Lets the player heal from an item
	void changeHealth(GameUI console, int _health);
	void displayHealth(GameUI console);

	// Turns the player's alive variable to false - meaning they were killed.
	void kill();
};