#include "Monster.h"
#include <string.h>
using namespace std;

// Constructors
Monster::Monster() {
	name = "";
	monsterDescription = "";
	dialogOpening = "";
}
Monster::Monster(string nameInput, string descrip, string openDialog) {
	name = nameInput;
	monsterDescription = descrip;
	dialogOpening = openDialog;
}

// Mutator Functions -- Functions that will be allowed to change private variables
void Monster::setName(string nameInput) {
	name = nameInput;
}
void Monster::setMonsterDescription(string descrip) {
	monsterDescription = descrip;
}
void Monster::setDialogOpening(string dialog) {
	dialogOpening = dialog;
}

// Accessor Functions -- Functions that will return values of private functions
string Monster::getName() {
	return name;
}
string Monster::getMonsterDescription() {
	return monsterDescription;
}
string Monster::getDialogOpening() {
	return dialogOpening;
}