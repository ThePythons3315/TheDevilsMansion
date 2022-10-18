#pragma once
#ifndef USERINTERFACE_H
#define USERINTERFACE_H

#include <iostream>
#include <string.h>
#include "Player.h"
using namespace std;

class UserInterface {
private:

public:
	// Constructors
	UserInterface();

	// Other Functions
	string getUserInput();
	string getUserInput(string);
	string convertLower(string);
	void printString(string);
};
#endif // !USERINTERFACE_H