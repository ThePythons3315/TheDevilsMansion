#include "Inventory.h"
using namespace std;

//Constructors
Inventory::Inventory()
{
	inventory = {};
}

//Funtion that adds items to inventory
void Inventory::addItem(Item item) {
	inventory.push_back(item);
}

//Function to display all the items in the player inventory
void Inventory::displayInventory()
{
	if (inventory.size() == 0) {
		cout << "There are no items." << endl;
	}
	else {
		cout << "Inventory includes: " << endl;
		for (int i = 0; i < inventory.size(); i++) {
			cout << "-" << inventory.at(i).getName() << endl;
		}
	}
}

int Inventory::getSize() {
	return inventory.size();
}

vector<Item> Inventory::getInventory() {
	return inventory;
}

void Inventory::removeItem(int index) {
	inventory.erase(inventory.begin() + index);
}