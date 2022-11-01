#pragma once
#ifndef WEAPON_H
#define WEAPON_H

#include <iostream>
#include <string>
#include "Attack.h"
using namespace std;

class Weapon {
private:
	string name;
	Attack attack1;
	Attack attack2;
public:
	// Constructors
	Weapon();
	Weapon(string, Attack, Attack);

	// Mutator Functions -- Functions that will be allowed to change private variables
	void setName(string);
	void setAttack1(Attack);
	void setAttack2(Attack);

	// Accessor Functions -- Functions that will return values of private functions
	string getName();
	Attack getAttack1();
	Attack getAttack2();
};
#endif // !WEAPON_H