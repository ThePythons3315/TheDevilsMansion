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

	// Mutator Functions
	void setStartingDescription(string);
	void setMainCharacter(Player);

	// Accessor Functions
	string getStartingDescription();
	Player getMainCharacter();

	// Other functions
	string acceptInputFromUser(string);
	void getPlayerInfo();

};
#endif // !USERINTERFACE_H