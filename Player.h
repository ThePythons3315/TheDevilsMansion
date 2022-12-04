#pragma once

#include <iostream>
#include <string>
#include "GameUI.h"
#include "Inventory.h"

class Player
{
private:
	std::string name;
	Inventory* inventory;
	int health;
	int maxHealth;
	bool alive;
public:
	// Constructors
	Player();
	Player(std::string _name, int _health, int _maxHealth, bool _alive);

	// Mutator Functions -- Functions that will be allowed to change private variables
	void setName(std::string _name);
	void setInventory(Inventory& _inventory);
	void setHealth(int _health);
	void setMaxHealth(int _maxHealth);
	void setAlive(bool _alive);

	// Accessor Functions -- Functions that will return values of private functions
	std::string getName();
	Inventory* getInventory();
	int getHealth();
	int getMaxHealth();
	bool getAlive();

	// Display functions
	void printPlayerInfo(GameUI console);
	void displayHealth(GameUI console);
	void displayBothHealth(GameUI console);

	// Lets the player heal from an item
	void useHealthItem(GameUI console, std::string item);
	void changeHealth(GameUI console, int _health);

	// Turns the player's alive variable to false - meaning they were killed.
	void kill();
};