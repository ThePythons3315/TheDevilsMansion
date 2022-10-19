#pragma once
#ifndef INVENTORY_H
#define INVENTORY_H

#include <iostream>
#include <string.h>

using namespace std;


class Inventory
{
private:

	string inventory[8];
	string item;

public:
	//constructors
	Inventory();
	Inventory(string);

	//Funtion that adds items to inventory
	void addItem(string);

	//Function to display all the items in the player inventory
	void displayInventory();

};


#endif // !INVENTORY_H
