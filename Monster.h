#pragma once
#ifndef MONSTER_H
#define MONSTER_H

#include <iostream>
#include <string.h>
#include "Health.h"
#include "Attacks.h"
#include "Inventory.h"
using namespace std;

class Monster {
private:
	string name;
	string monsterDescription;
	string dialogOpening;
	Health health;
	Attacks attacks;
	Inventory monsterInventory;
public:
	// Constructors
	Monster();
	Monster(string, string, string, Health,Attacks);
	Monster(string, string, string, Health, Attacks, Inventory);

	// Mutator Functions -- Functions that will be allowed to change private variables
	void setName(string);
	void setMonsterDescription(string);
	void setDialogOpening(string);
	void setHealth(Health);
	void setAttacks(Attacks);
	void setInventory(Inventory);

	// Accessor Functions -- Functions that will return values of private functions
	string getName();
	string getMonsterDescription();
	string getDialogOpening();
	Health getHealth();
	Attacks getAttacks();
	Inventory getInventory();

	void displayMonster();
};
#endif // !PLAYER_H