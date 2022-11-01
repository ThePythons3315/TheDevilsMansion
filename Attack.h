#pragma once
#ifndef ATTACK_H
#define ATTACK_H

#include <iostream>
#include <string>
using namespace std;

class Attack {
private:
	string name;
	int damage;
public:
	// Constructors
	Attack();
	Attack(string, int);

	// Mutator Functions -- Functions that will be allowed to change private variables
	void setName(string);
	void setDamage(int);

	// Accessor Functions -- Functions that will return values of private functions
	string getName();
	int getDamage();
	
};
#endif // !ATTACK_H