#pragma once

#include <iostream>
#include <string>
#include "GameUI.h"

class Attack
{
private:
	std::string name;
	std::string description;
	int damage;
	double hitChance;
	int statusEffect;
	int statusEffectHitChance;
public:
	// Constructors
	Attack();
	Attack(std::string _name, std::string _description, int _damage, int _hitChance, int _statusEffect, int _statusEffectHitChance);

	// Mutator Functions -- Functions that will be allowed to change private variables
	void setName(std::string _name);
	void setDescription(std::string _description);
	void setDamage(int _damage);
	void setHitChance(int _hitChance);
	void setStatusEffect(int _statusEffect);
	void setStatusEffectHitChance(int _statusEffectHitChance);

	// Accessor Functions -- Functions that will return values of private functions
	std::string getName();
	std::string getDescription();
	int getDamage();
	int getHitChance();
	int getStatusEffect();
	int getStatusEffectHitChance();

	// Displays the stats of the attack
	void displayAttack(GameUI console);
	void displayAttackStats(GameUI console);
};