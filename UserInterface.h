#pragma once
#ifndef USERINTERFACE_H
#define USERINTERFACE_H

#include <iostream>
#include <string.h>
using namespace std;

class UserInterface {
private:
	string startingDescription;
public:
	// Constructors
	UserInterface();

	// Mutator Functions
	void setStartingDescription(string);

	// Accessor Functions
	string getStartingDescription();
};
#endif // !USERINTERFACE_H