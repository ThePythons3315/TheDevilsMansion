#pragma once
#ifndef PLAYER_H
#define PLAYER_H

#include <iostream>
#include <string.h>
using namespace std;

class Player {
private:
	string name;
public:
	// Constructors
	Player();
	Player(string);

	// Mutator Functions
	void setName(string);

	// Accessor Functions
	string getName();
};
#endif // !PLAYER_H