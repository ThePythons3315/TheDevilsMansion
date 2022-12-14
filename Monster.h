#pragma once

#include <iostream>
#include <string>
#include "GameUI.h"
#include "Inventory.h"

class Monster
{
private:
	std::string name;
	std::string description;
	Inventory* inventory;
	int health;
	int maxHealth;
	bool alive;
	int statusEffect;
	int statusEffectHitChance;
public:
	// Constructors
	Monster();
	Monster(std::string _name, std::string _description, int _health, int _maxHealth, bool _alive, int statusEffect, int _statusEffectHitChance);

	// Mutator Functions -- Functions that will be allowed to change private variables
	void setName(std::string _name);
	void setDescription(std::string _name);
	void setInventory(Inventory& _inventory);
	void setHealth(int _health);
	void setMaxHealth(int _maxHealth);
	void setAlive(bool _alive);
	void setStatusEffect(int _statusEffect);
	void setStatusEffectHitChance(int _statusEffectHitChance);

	// Accessor Functions -- Functions that will return values of private functions
	std::string getName();
	std::string getDescription();
	Inventory* getInventory();
	int getHealth();
	int getMaxHealth();
	bool getAlive();
	int getStatusEffect();
	int getStatusEffectHitChance();

	// Prints all of the mosnter's attributes to the screen - mainly for testing.
	void printMonsterInfo(GameUI console);
	void printMonsterInRoom(GameUI console);
	void viewMonster(GameUI console, bool* inBattle);

	// Lets us change the monster's health
	void changeHealth(GameUI console, int _health);
	void displayHealth(GameUI console);

	// Deals with status conditions
	bool checkParalyzed();
	bool checkBurned();
	void performBurn(GameUI console);

	// Turns the player's alive variable to false - meaning they were killed.
	void kill();
};