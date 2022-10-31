#pragma once
#ifndef BATTLE_H
#define BATTLE_H

#include <iostream>
#include <string>
#include "Player.h"
#include "Monster.h"
using namespace std;


class Battle
{
private:
	Player player;
	Monster monster;
public:
	//constructors
	Battle();
	Battle(Player, Monster);

	// Mutator Functions -- Functions that will be allowed to change private variables
	void setPlayer(Player);
	void setMonster(Monster);

	// Accessor Functions -- Functions that will return values of private functions
	Player getPlayer();
	Monster getMonster();

	void displayOpeningLine();
};


#endif // !HEALTH_H