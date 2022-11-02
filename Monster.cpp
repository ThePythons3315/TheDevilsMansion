#include "Monster.h"
#include <string.h>
using namespace std;

// Constructors
Monster::Monster() {
	name = "";
	monsterDescription = "";
	dialogOpening = "";
	health;
	weapon;
}
Monster::Monster(string _name, string _monsterDescription, string _dialogOpening, Health _health, Weapon _weapon) {
	name = _name;
	monsterDescription = _monsterDescription;
	dialogOpening = _dialogOpening;
	health = _health;
	weapon = _weapon;
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
void Monster::setWeapon(Weapon _weapon) {
	weapon = _weapon;
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
Weapon Monster::getWeapon() {
	return weapon;
}

void Monster::displayMonster() {
	cout << "In front of you is a " << name << endl;
	cout << "The " << name << "'s ";
	health.displayHealth();
}