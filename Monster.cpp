#include "Monster.h"
#include <string.h>
using namespace std;

// Constructors
Monster::Monster() {
	name = "";
	description = "";
}
Monster::Monster(string name_input, string descrip) {
	name = name_input;
	description = descrip;
}

// Mutator Functions
void Monster::setName(string n) {
	name = n;
}
void Monster::setDescription(string d) {
	description = d;
}

// Accessor Functions
string Monster::getName() {
	return name;
}
string Monster::getDescription() {
	return description;
}