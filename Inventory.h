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
	void displayInventory();

};


#endif // !INVENTORY_H
