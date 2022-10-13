#pragma once
#ifndef MONSTER_H
#define MONSTER_H

#include <iostream>
#include <string.h>
using namespace std;

class Monster {
private:
	string name;
	string monsterDescription;
	string dialogOpening;
public:
	// Constructors
	Monster();
	Monster(string, string, string);

	// Mutator Functions -- Functions that will be allowed to change private variables
	void setName(string);
	void setMonsterDescription(string);
	void setDialogOpening(string);

	// Accessor Functions -- Functions that will return values of private functions
	string getName();
	string getMonsterDescription();
	string getDialogOpening();
};
#endif // !PLAYER_H