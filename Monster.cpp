#include "Monster.h"

// Constructors
Monster::Monster()
{
	name = "";
	description = "";
	inventory = new Inventory();
	health = 100;
	maxHealth = 100;
}
Monster::Monster(std::string _name, std::string _description, int _health, int _maxHealth, bool _alive, int _statusEffect, int _statusEffectHitChance)
{
	name = _name;
	description = _description;
	inventory = new Inventory();
	health = _health;
	maxHealth = _maxHealth;
	alive = _alive;
	statusEffect = _statusEffect;
	statusEffectHitChance = _statusEffectHitChance;
}

// Mutator Functions -- Functions that will be allowed to change private variables
void Monster::setName(std::string _name)
{
	name = _name;
}
void Monster::setDescription(std::string _description)
{
	description = _description;
}
void Monster::setInventory(Inventory& _inventory)
{
	inventory = &_inventory;
}
void Monster::setHealth(int _health)
{
	health = _health;
}
void Monster::setMaxHealth(int _maxHealth)
{
	maxHealth = _maxHealth;
}
void Monster::setAlive(bool _alive)
{
	alive = _alive;
}
void Monster::setStatusEffect(int _statusEffect)
{
	statusEffect = _statusEffect;
}
void Monster::setStatusEffectHitChance(int _statusEffectHitChance)
{
	statusEffectHitChance = _statusEffectHitChance;
}

// Accessor Functions -- Functions that will return values of private functions
std::string Monster::getName()
{
	return name;
}
std::string Monster::getDescription()
{
	return description;
}
Inventory* Monster::getInventory()
{
	return inventory;
}
int Monster::getHealth()
{
	return health;
}
int Monster::getMaxHealth()
{
	return maxHealth;
}
bool Monster::getAlive()
{
	return alive;
}
int Monster::getStatusEffect()
{
	return statusEffect;
}
int Monster::getStatusEffectHitChance()
{
	return statusEffectHitChance;
}

// Prints all of the monster's attributes to the screen - mainly for testing.
void Monster::printMonsterInfo(GameUI console)
{
	// Text messages to user
	std::string extraNewline = "\n";
	std::string header = "Monster's information includes:\n\n";
	std::string monsterName = "Monster Name: " + name + "\n\n";
	std::string monsterDescription = "Monster Description: " + description + "\n";

	// Display basic monster info
	console.outputByCharacter(header);
	console.outputByCharacter(monsterName);
	console.outputByCharacter(monsterDescription);

	// Show the monster's inventory
	console.outputByCharacter(extraNewline);
	inventory->displayItemInventory(console, "Monster");

	// Show the monster's health
	console.outputByCharacter(extraNewline);
	displayHealth(console);
	console.outputByCharacter(extraNewline);
}

// Print only the monster's name 
void Monster::printMonsterInRoom(GameUI console)
{
	// Text messages to the user
	std::string defeatedMessage = "\n" + name + " has already been defeated.\n";
	std::string inFrontOfMessage = "\nIn front of you there is a " + name;
	std::string healthMessage = "\nThe " + name + "'s health is currently " + std::to_string(health) + ".\n";
	std::string noMonsterInRoom = "\nThere is currently no monster in this room to battle.\n";

	// If there is a monster in the room, then display the monster to the user
	if (name != "")
	{
		// Check to see if the monster has been defeated already
		if (health <= 0)
		{
			// Display that the monster has already been defeated if they have been
			console.outputByCharacter(defeatedMessage);
		}
		else
		{
			// Print if there are any monsters in the room or not
			console.outputByCharacter(inFrontOfMessage);
			console.outputByCharacter(healthMessage);
		}
	}
	else
	{
		// Display that there is no monster in the current room
		console.outputByCharacter(noMonsterInRoom);
	}
}

// Displays the apprropriate attributes of the monster when using the view command
void Monster::viewMonster(GameUI console, bool* inBattle)
{
	// Text messages to the user
	std::string monsterName = "Monster Name: " + name + ".\n\n";
	std::string monsterDescription = description + "\n\n";
	std::string monsterHealth = "The " + name + "'s health: " + std::to_string(health) + ".\n";
	std::string monsterStatus = "\nStatus Effect: ";

	// Display the monster's information
	console.outputByCharacter(monsterName);
	console.outputByCharacter(monsterDescription);
	console.outputByCharacter(monsterHealth);

	// If in battle, also print out whether the monster has a status condition or not
	if (*inBattle == true)
	{
		// Add the status condition to the string
		if (statusEffect == 0)
		{
			// No status effect
			monsterStatus += "None.\n";
		}
		else if (statusEffect == 1)
		{
			// Monster is paralyzed
			monsterStatus += "Paralyzed.\n";
		}
		else if (statusEffect == 2)
		{
			// Monster is burned
			monsterStatus += "Burned.\n";
		}

		// Display the status condition
		console.outputByCharacter(monsterStatus);
	}
}

// Change the monster's health value
void Monster::changeHealth(GameUI console, int _health)
{
	// Text message to the user
	std::string healthMessage = "\n\tUsing this item has caused your health to exceed the max health allowed to the monster.\n"
								"\tThe monster's health will be set to " + std::to_string(getMaxHealth()) + ".\n";

	// Update the health attribute
	health = getHealth() + _health;

	// Check to see if the current health exceeds the max health
	if (health > maxHealth)
	{
		// Tell the player that their health will be placed at the max allowed health
		console.outputByCharacter(healthMessage);

		// Set the health attribute to the maxHealth attributes value
		health = maxHealth;
	}
}

// Print the monster's health to the screen
void Monster::displayHealth(GameUI console)
{
	// Text message to the user
	std::string healthMessage = "\Monster's Health: " + std::to_string(getHealth()) + ".\n";

	// Display the health of the monster
	console.outputByCharacter(healthMessage);
}

///////////////////////////////////////////////////////////////////////////////////////////
// Deals with status conditions
///////////////////////////////////////////////////////////////////////////////////////////

// Checks for paralysis
bool Monster::checkParalyzed()
{
	// Check to see if the player is paralyzed
	if (statusEffect == 1)
	{
		// The player is paralyzed
		return true;
	}
	else
	{
		// The player is not paralyzed
		return false;
	}
}

// Checks for burn
bool Monster::checkBurned()
{
	// Check to see if the player is paralyzed
	if (statusEffect == 2)
	{
		// The player is paralyzed
		return true;
	}
	else
	{
		// The player is not paralyzed
		return false;
	}
}

// The monster is burned, take away an extra 5 hp from the monster
void Monster::performBurn(GameUI console)
{
	// Burn damage
	int damage = 5;

	// Output message to tell the user the burn has affected the monster
	std::string outputMessage = "The monster's burn has hit them for an extra " + std::to_string(damage) + " damage.\n";

	// Take away the 5 burn damage when this function is called
	health = health - damage;

	// Display that the burn has taken affect
	console.outputByCharacter(outputMessage);
}

// Turns the monster's alive variable to false - meaning they were killed.
void Monster::kill()
{
	// Kill the monster - mwah ha ha ha
	alive = false;
}