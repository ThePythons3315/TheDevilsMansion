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

// Mutator Functions
void Monster::setName(string nameInput) {
	name = nameInput;
}
void Monster::setMonsterDescription(string descrip) {
	monsterDescription = descrip;
}
void Monster::setDialogOpening(string dialog) {
	dialogOpening = dialog;
}

// Accessor Functions
string Monster::getName() {
	return name;
}
string Monster::getMonsterDescription() {
	return monsterDescription;
}
string Monster::getDialogOpening() {
	return dialogOpening;
}