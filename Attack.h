#pragma once

#include <iostream>
#include <string>
#include "GameUI.h"

class Attack
{
private:
	std::string name;
	int damage;
	double hitChance;
public:
	// Constructors
	Attack();
	Attack(std::string _name, int _damage, int _hitChance);

	// Mutator Functions -- Functions that will be allowed to change private variables
	void setName(std::string _name);
	void setDamage(int _damage);
	void setHitChance(int _hitChance);

	// Accessor Functions -- Functions that will return values of private functions
	std::string getName();
	int getDamage();
	int getHitChance();

	// Displays the stats of the attack
	void displayAttackStats(GameUI console);
};