#pragma once

#include <iostream>
#include <string>
#include "Room.h"
#include "Player.h"
#include "Monster.h"
#include "GameUI.h"

class Battle
{
private:
	Room* roomPointer = nullptr;
	Player player;
	Monster monster;
public:
	// Constructors
	Battle();
	Battle(Room*&, Player, Monster);

	// Mutator Functions -- Functions that will be allowed to change private variables
	void setRoom(Room*&);
	void setPlayer(Player);
	void setMonster(Monster);

	// Accessor Functions -- Functions that will return values of private functions
	Room getRoom();
	Player getPlayer();
	Monster getMonster();

	// Function to display that the player is now in battle against a monster
	void displayOpeningLine();

	// Main battle function that will loop until battle is finished
	void runBattle();

	// Validate that the input from the user is a correct command.
	// Correct commands will be in the keyWords vector.
	bool validateInput(vector<string>& vect, string sentence);

	// Calculates whether an attack will hit or miss the target
	bool hitOrMiss(int hitChance);
	
	//Checks to ensure the monsters or health is above 0 to decide whether
	//to end the battle or continue letting the player battle the monster.
	bool monsterDefeated();
	bool playerDefeated();
};