#pragma once
#ifndef MONSTER_H
#define MONSTER_H

#include <iostream>
#include <string.h>
using namespace std;

class Monster {
private:
	string name;
	string description;
public:
	// Constructors
	Monster();
	Monster(string, string);

	// Mutator Functions
	void setName(string);
	void setDescription(string);

	// Accessor Functions
	string getName();
	string getDescription();
};
#endif // !PLAYER_H