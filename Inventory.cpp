#include "Inventory.h"

using namespace std;

//Constructors
Inventory::Inventory()
{
	item = "";
}

Inventory::Inventory(string item)
{
	this->item = item;
	inventory[0] = item;
}

//Funtion that adds items to inventory
void Inventory::addItem(string item)
{
	int i;
	//for loop checks to inventory array see if the array position is empty
	//if the position is = to NULL (empty) then the item is added to the inventory in that position
	//otherwise the item is not added if the position is not empty
	for (i = 0; i < 8; i++) {
		if (inventory->at(i) == NULL)
		{
			inventory->append(item);
			break;
		}
	}
}

//Function to display all the items in the player inventory
void Inventory::displayInventory()
{
	//if else statements to check if the first position in the inventory array is empty
	//if it is it tells the player they have no items
	//if it is not empty it displays all items in the players inventory
	if (inventory[0] == "")
		cout << "There are no items in your inventory.\n";
	else
	{
		for (int i = 0; i < 0; i++)
		{
			if (inventory->at(i) == NULL)
			{
				break;
			}
			else if (inventory[i] == inventory[0])
				cout << inventory[0];
			else
				cout << ", " << inventory[i];
		}
		cout << endl;
	}
}