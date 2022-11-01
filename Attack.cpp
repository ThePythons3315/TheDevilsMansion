#include "Attack.h"
using namespace std;

// Constructors
Attack::Attack() {
	name = "";
	damage = 0;
}
Attack::Attack(string _name, int _damage) {
	name = _name;
	damage = _damage;
}

// Mutator Functions -- Functions that will be allowed to change private variables
void Attack::setName(string _name) {
	name = _name;
}
void Attack::setDamage(int _damage) {
	damage = _damage;
}

// Accessor Functions -- Functions that will return values of private functions
string Attack::getName() {
	return name;
}
int Attack::getDamage() {
	return damage;
}