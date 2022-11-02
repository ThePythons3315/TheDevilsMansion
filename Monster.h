#pragma once
#ifndef MONSTER_H
#define MONSTER_H

#include <iostream>
#include <string.h>
#include "Health.h"
#include "Weapon.h"
using namespace std;

class Monster {
private:
	string name;
	string monsterDescription;
	string dialogOpening;
	Health health;
	Weapon weapon;
public:
	// Constructors
	Monster();
	Monster(string, string, string, Health, Weapon);

	// Mutator Functions -- Functions that will be allowed to change private variables
	void setName(string);
	void setMonsterDescription(string);
	void setDialogOpening(string);
	void setHealth(Health);
	void setWeapon(Weapon);

	// Accessor Functions -- Functions that will return values of private functions
	string getName();
	string getMonsterDescription();
	string getDialogOpening();
	Health getHealth();
	Weapon getWeapon();

	void displayMonster();
};
#endif // !PLAYER_H