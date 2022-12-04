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
Monster::Monster(std::string _name, std::string _description, int _health, int _maxHealth, bool _alive)
{
	name = _name;
	description = _description;
	inventory = new Inventory();
	health = _health;
	maxHealth = _maxHealth;
	alive = _alive;
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

// Prints all of the monster's attributes to the screen - mainly for testing.
void Monster::printMonsterInfo(GameUI console)
{
	// Text messages to user
	std::string extraNewline = "\n";
	std::string header = "Monster's information includes:\n\n";
	std::string monsterName = "Monster Name: " + name + "\n\n";
	std::string monsterDescription = "Monster Description: " + description + "\n";

	// Display basic monster info
	console.writeOutput(header);
	console.writeOutput(monsterName);
	console.writeOutput(monsterDescription);

	// Show the monster's inventory
	console.writeOutput(extraNewline);
	inventory->displayItemInventory(console, "Monster");

	// Show the monster's health
	console.writeOutput(extraNewline);
	displayHealth(console);
	console.writeOutput(extraNewline);
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
			console.writeOutput(defeatedMessage);
		}
		else
		{
			// Print if there are any monsters in the room or not
			console.writeOutput(inFrontOfMessage);
			console.writeOutput(healthMessage);
		}
	}
	else
	{
		// Display that there is no monster in the current room
		console.writeOutput(noMonsterInRoom);
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
		console.writeOutput(healthMessage);

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
	console.writeOutput(healthMessage);
}

// Turns the monster's alive variable to false - meaning they were killed.
void Monster::kill()
{
	// Kill the monster - mwah ha ha ha
	alive = false;
}