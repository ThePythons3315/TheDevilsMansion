#pragma once
#ifndef USERINTERFACE_H
#define USERINTERFACE_H

#include <iostream>
#include <string.h>
#include "Player.h"
using namespace std;

class UserInterface {
private:
	string startingDescription;
	
	Player mainCharacter;

public:
	// Constructors
	UserInterface();

	// Mutator Functions -- Functions that will be allowed to change private variables
	void setStartingDescription(string);
	void setMainCharacter(Player);

	// Accessor Functions -- Functions that will return values of private functions
	string getStartingDescription();
	Player getMainCharacter();

	// Accepts input from user
	string acceptInputFromUser(string);

	// Gets info of player, creates the player object
	void getPlayerInfo();

};
#endif // !USERINTERFACE_H