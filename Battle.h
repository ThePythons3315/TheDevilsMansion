#pragma once
#ifndef BATTLE_H
#define BATTLE_H

#include <iostream>
#include <string>
#include "Player.h"
#include "Monster.h"
#include "UserInterface.h"
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

	// Function to display that the player is now in battle against a monster
	void displayOpeningLine();

	// Main battle function that will loop until battle is finished
	void runBattle();

	// Validate that the input from the user is a correct command.
	// Correct commands will be in the keyWords vector.
	bool validateInput(vector<string>& vect, string sentence);

	void attackMonster(int);
};


#endif // !HEALTH_H