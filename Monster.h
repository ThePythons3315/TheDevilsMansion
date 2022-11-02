#pragma once
#ifndef MONSTER_H
#define MONSTER_H

#include <iostream>
#include <string.h>
#include "Health.h"
#include "Attacks.h"
using namespace std;

class Monster {
private:
	string name;
	string monsterDescription;
	string dialogOpening;
	Health health;
	Attacks attacks;
public:
	// Constructors
	Monster();
	Monster(string, string, string, Health,Attacks);

	// Mutator Functions -- Functions that will be allowed to change private variables
	void setName(string);
	void setMonsterDescription(string);
	void setDialogOpening(string);
	void setHealth(Health);
	void setAttacks(Attacks);

	// Accessor Functions -- Functions that will return values of private functions
	string getName();
	string getMonsterDescription();
	string getDialogOpening();
	Health getHealth();
	Attacks getAttacks();

	void displayMonster();
};
#endif // !PLAYER_H