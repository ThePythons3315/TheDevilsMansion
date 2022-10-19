#pragma once
#ifndef PLAYER_H
#define PLAYER_H

#include <iostream>
#include <string>
using namespace std;

class Player {
private:
	string name;
public:
	// Constructors
	Player();
	Player(string);

	// Mutator Functions -- Functions that will be allowed to change private variables
	void setName(string);

	// Accessor Functions -- Functions that will return values of private functions
	string getName();
};
#endif // !PLAYER_H