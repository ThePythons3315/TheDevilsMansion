#pragma once
#ifndef HEALTH_H
#define HEALTH_H

#include <iostream>
#include <string>
using namespace std;


class Health
{
private:
	int health;
	int maxHealth;
public:
	//constructors
	Health();
	Health(int, int);

	// Mutator Functions -- Functions that will be allowed to change private variables
	void setHealth(int);
	void setMaxHealth(int);

	// Accessor Functions -- Functions that will return values of private functions
	int getHealth();
	int getMaxHealth();
};


#endif // !HEALTH_H