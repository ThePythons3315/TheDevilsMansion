#include "Monster.h"
#include <string.h>
using namespace std;

// Constructors
Monster::Monster() {
	name = "";
	monsterDescription = "";
	dialogOpening = "";
	health;
	attacks;
	monsterInventory;
}
Monster::Monster(string _name, string _monsterDescription, string _dialogOpening, Health _health, Attacks _attacks) {
	name = _name;
	monsterDescription = _monsterDescription;
	dialogOpening = _dialogOpening;
	health = _health;
	attacks = _attacks;
	monsterInventory;
}

Monster::Monster(string _name, string _monsterDescription, string _dialogOpening, Health _health, Attacks _attacks, Inventory inventory)
{
	name = _name;
	monsterDescription = _monsterDescription;
	dialogOpening = _dialogOpening;
	health = _health;
	attacks = _attacks;
	monsterInventory = inventory;
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
void Monster::setAttacks(Attacks _attacks) {
	attacks = _attacks;
}

void Monster::setInventory(Inventory inventory)
{
	monsterInventory = inventory;
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
Attacks Monster::getAttacks() {
	return attacks;
}

Inventory Monster::getInventory()
{
	return monsterInventory;
}

void Monster::displayMonster() {
	cout << "In front of you is a " << name << endl;
	cout << "The " << name << "'s ";
	health.displayHealth();
	//attacks.displayattacks();
}