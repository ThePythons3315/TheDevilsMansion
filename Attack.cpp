#include "Attack.h"

// Constructors
Attack::Attack()
{
	name = "";
	description = "";
	damage = 0;
	hitChance = 0;
	statusEffect = 0;
	statusEffectHitChance = 0;
}
Attack::Attack(std::string _name, std::string _description, int _damage, int _hitChance, int _statusEffect, int _statusEffectHitChance)
{
	name = _name;
	description = _description;
	damage = _damage;
	hitChance = _hitChance;
	statusEffect = _statusEffect;
	statusEffectHitChance = _statusEffectHitChance;
}

// Mutator Functions -- Functions that will be allowed to change private variables
void Attack::setName(std::string _name)
{
	name = _name;
}
void Attack::setDescription(std::string _description)
{
	description = _description;
}
void Attack::setDamage(int _damage)
{
	damage = _damage;
}
void Attack::setHitChance(int _hitChance)
{
	hitChance = _hitChance;
}
void Attack::setStatusEffect(int _statusEffect)
{
	statusEffect = _statusEffect;
}
void Attack::setStatusEffectHitChance(int _statusEffectHitChance)
{
	statusEffectHitChance = _statusEffectHitChance;
}

// Accessor Functions -- Functions that will return values of private functions
std::string Attack::getName()
{
	return name;
}
std::string Attack::getDescription()
{
	return description;
}
int Attack::getDamage()
{
	return damage;
}
int Attack::getHitChance()
{
	return hitChance;
}
int Attack::getStatusEffect()
{
	return statusEffect;
}
int Attack::getStatusEffectHitChance()
{
	return statusEffectHitChance;
}

// Displays the stats of the attack
void Attack::displayAttack(GameUI console)
{
	// Text messages to the user
	std::string attackName = name;

	// Display the attack's stats
	console.writeOutput(attackName);
}

// Displays the stats of the attack
void Attack::displayAttackStats(GameUI console)
{
	// Text messages to the user
	std::string attackName = name + ":\n";
	std::string attackDescription = "-Description: " + description + "\n";
	std::string attackDamage = "-Damage: " + std::to_string(damage * -1) + ".\n";
	std::string attackHitChance = "-Hit Chance: " + std::to_string(int(hitChance)) + "%.\n";
	std::string status = "-Status Effect: None.\n";
	std::string statusHitChance = "";

	// Change the outputs based on whether the attack has a status effect or not
	if (statusEffect == 1)
	{
		status = "-Status Effect: Paralysis.\n";
		statusHitChance = "-Status Effect Hit Chance: " + std::to_string(statusEffectHitChance) + ".\n";
	}
	else if (statusEffect == 2)
	{
		status = "-Status Effect: Burn.\n";
		statusHitChance = "-Status Effect Hit Chance: " + std::to_string(statusEffectHitChance) + ".\n";
	}
	
	// Display the attack's stats
	console.writeOutput(attackName);
	console.writeOutput(attackDescription);
	console.writeOutput(attackDamage);
	console.writeOutput(attackHitChance);
	console.writeOutput(status);
	console.writeOutput(statusHitChance);
}