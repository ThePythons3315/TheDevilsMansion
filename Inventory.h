#pragma once

#include <iostream>
#include <string>
#include <list>
#include "GameUI.h"
#include "Item.h"
#include "Attack.h"

class Inventory
{
private:
	// List of pointers to item objects
	std::list<Item*> itemInventory;
	std::list<Attack*> attackInventory;
public:
	// Constructor
	Inventory();

	// Returns the size of the itemInventory
	int getItemInventorySize();

	// Adds an item object to the item inventory list
	void addItem(Item& _item);
	void addAttack(GameUI console, Attack& _attack);

	// Returns a pointer to the address of the specified item
	Item* getItem(GameUI console, std::string item);
	Attack* getAttack(GameUI console);
	Attack* getAttack(GameUI console, std::string attack);

	// Displays all of the items in the item inventory
	void displayItemInventory(GameUI console, std::string _type);
	void displayAttackInventory(GameUI console, std::string _type);

	// Remove an item from the item inventory
	void removeItem(GameUI console, std::string item);
	void removeAttack(GameUI console, std::string attack);

	// Searches the item inventory list and returns true or false based on
	// if the item was found or not
	bool searchItemInventory(std::string item);
	bool searchAttackInventory(std::string attack);

	// Returns the size of the attack inventory
	int getAttackInventorySize();
};