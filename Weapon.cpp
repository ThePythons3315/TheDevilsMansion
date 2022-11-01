#include "Weapon.h"
using namespace std;

// Constructors
Weapon::Weapon() {
	name = "";
	attack1;
	attack2;
}
Weapon::Weapon(string _name, Attack _attack1, Attack _attack2) {
	name = _name;
	attack1 = _attack1;
	attack2 = _attack2;
}

// Mutator Functions -- Functions that will be allowed to change private variables
void Weapon::setName(string _name) {
	name = _name;
}
void Weapon::setAttack1(Attack _attack1) {
	attack1 = _attack1;
}
void Weapon::setAttack2(Attack _attack2) {
	attack2 = _attack2;
}

// Accessor Functions -- Functions that will return values of private functions
string Weapon::getName() {
	return name;
}
Attack Weapon::getAttack1() {
	return attack1;
}
Attack Weapon::getAttack2() {
	return attack2;
}