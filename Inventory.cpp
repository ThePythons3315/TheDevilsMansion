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

//Function to display all the items in the room inventory
void Inventory::displayRoomInventory()
{
	cout << "Items in the room include: " << endl;
	if (inventory.size() == 0) {
		cout << "-" << endl;
	}
	else {
		for (int i = 0; i < inventory.size(); i++) {
			cout << "-" << inventory.at(i).getName() << endl;
		}
	}
	//std::cout << std::endl; // ToDo: Figure out a way to take this out to make the spacing work
}

//Function to display all the items in the player inventory
void Inventory::displayPlayerInventory()
{
	cout << "Player inventory includes: " << endl;
	if (inventory.size() == 0) {
		cout << "-" << endl;
	}
	else {
		for (int i = 0; i < inventory.size(); i++) {
			cout << "-" << inventory.at(i).getName() << endl;
		}
	}
	//std::cout << std::endl; // ToDo: Figure out a way to take this out to make the spacing work
}

void Inventory::displayMonsterInventory()
{
	cout << "Monster inventory includes: " << endl;
	if (inventory.size() == 0) {
		cout << "-" << endl;
	}
	else {
		for (int i = 0; i < inventory.size(); i++) {
			cout << "-" << inventory.at(i).getName() << endl;
		}
	}
	cout << endl;
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