#include "Item.h"
#include <string>
using namespace std;

// Constructors
Item::Item() {
	name = "";
	health = 0;
}
Item::Item(string nameInput, int itemHealth) {
	name = nameInput;
	health = itemHealth;
}

// Mutator Functions -- Functions that will be allowed to change private variables
void Item::setName(string nameInput) {
	name = nameInput;
}
void Item::setHealth(int itemHealth) {
	health = itemHealth;
}

// Accessor Functions -- Functions that will return values of private functions
string Item::getName() {
	return name;
}
int Item::getHealth() {
	return health;
}