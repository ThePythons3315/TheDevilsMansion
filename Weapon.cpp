#include "Weapon.h"
using namespace std;

// Constructors
Weapon::Weapon() {
	name = "";
	attackName = "";
	attackDamage = 0;
}
Weapon::Weapon(string _name, string _attackName, int _attackDamage) {
	name = _name;
	attackName = _attackName;
	attackDamage = _attackDamage;
}

// Mutator Functions -- Functions that will be allowed to change private variables
void Weapon::setName(string _name) {
	name = _name;
}
void Weapon::setAttackName(string _attackName) {
	attackName = _attackName;
}
void Weapon::setAttackDamage(int _attackDamage) {
	attackDamage = _attackDamage;
}

// Accessor Functions -- Functions that will return values of private functions
string Weapon::getName() {
	return name;
}
string Weapon::getAttackName() {
	return attackName;
}
int Weapon::getAttackDamage() {
	return attackDamage;
}