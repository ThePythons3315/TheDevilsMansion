#include "Item.h"
#include <string>
using namespace std;

// Constructors
Item::Item() {
	name = "";
}
Item::Item(string nameInput) {
	name = nameInput;
}

// Mutator Functions -- Functions that will be allowed to change private variables
void Item::setName(string nameInput) {
	name = nameInput;
}

// Accessor Functions -- Functions that will return values of private functions
string Item::getName() {
	return name;
}