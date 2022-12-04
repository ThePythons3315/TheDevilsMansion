#include "Attack.h"

// Constructors
Attack::Attack()
{
	name = "";
	damage = 0;
	hitChance = 0;
}
Attack::Attack(std::string _name, int _damage, int _hitChance)
{
	name = _name;
	damage = _damage;
	hitChance = _hitChance;
}

// Mutator Functions -- Functions that will be allowed to change private variables
void Attack::setName(std::string _name)
{
	name = _name;
}
void Attack::setDamage(int _damage)
{
	damage = _damage;
}
void Attack::setHitChance(int _hitChance)
{
	hitChance = _hitChance;
}

// Accessor Functions -- Functions that will return values of private functions
std::string Attack::getName()
{
	return name;
}
int Attack::getDamage()
{
	return damage;
}
int Attack::getHitChance()
{
	return hitChance;
}

// Displays the stats of the attack
void Attack::displayAttackStats(GameUI console)
{
	// Text messages to the user
	std::string attackName = name + ":\n";
	std::string attackDamage = "-Damage: " + std::to_string(damage * -1) + ".\n";
	std::string attackHitChance = "-Hit Chance: " + std::to_string(int(hitChance)) + "%.\n";

	// Display the attack's stats
	console.writeOutput(attackName);
	console.writeOutput(attackDamage);
	console.writeOutput(attackHitChance);
}