#pragma once
#ifndef INVENTORY_H
#define INVENTORY_H

#include <iostream>
#include <string>
#include <vector>
#include "Item.h"
using namespace std;


class Inventory
{
private:
	vector<Item> inventory;
public:
	//constructors
	Inventory();

	//Funtion that adds items to inventory
	void addItem(Item);

	//Function to display all the items in the player inventory
	void displayRoomInventory();
	void displayPlayerInventory();
	void displayMonsterInventory();

	// Get the number of items being stored in the inventory
	int getSize();

	// Function that returns a vector of the items in the inventory
	vector<Item> getInventory();

	// Remove an item from the inventory
	void removeItem(int);

};


#endif // !INVENTORY_H
