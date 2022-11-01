#pragma once
#ifndef WEAPON_H
#define WEAPON_H

#include <iostream>
#include <string>
using namespace std;

class Weapon {
private:
	string name;
	string attackName;
	int attackDamage;
public:
	// Constructors
	Weapon();
	Weapon(string, string, int);

	// Mutator Functions -- Functions that will be allowed to change private variables
	void setName(string);
	void setAttackName(string);
	void setAttackDamage(int);

	// Accessor Functions -- Functions that will return values of private functions
	string getName();
	string getAttackName();
	int getAttackDamage();
	
};
#endif // !WEAPON_H