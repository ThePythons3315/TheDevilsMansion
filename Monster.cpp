#include "Monster.h"
#include <string.h>
using namespace std;

// Constructors
Monster::Monster() {
	name = "";
	monsterDescription = "";
	dialogOpening = "";
	health;
}
Monster::Monster(string nameInput, string descrip, string openDialog, Health hp) {
	name = nameInput;
	monsterDescription = descrip;
	dialogOpening = openDialog;
	health = hp;
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
void Monster::setHealth(Health hp) {
	health = hp;
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
Health Monster::getHealth() {
	return health;
}

void Monster::displayMonster() {
	cout << "In front of you is a " << name << endl;
	cout << "The " << name << "'s ";
	health.displayHealth();
}