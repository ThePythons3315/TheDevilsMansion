#include "Player.h"

// Constructors
Player::Player()
{
	name = "";
	inventory;
	health = 100;
	maxHealth = 100;
	alive = true;
	statusEffect = 0;
}
Player::Player(std::string _name, int _health, int _maxHealth, bool _alive, int _statusEffect, int _statusEffectHitChance)
{
	name = _name;
	inventory;
	health = _health;
	maxHealth = _maxHealth;
	alive = _alive;
	statusEffect = _statusEffect;
	statusEffectHitChance = _statusEffectHitChance;
}

// Mutator Functions -- Functions that will be allowed to change private variables
void Player::setName(std::string _name)
{
	name = _name;
}
void Player::setInventory(Inventory& _inventory)
{
	inventory = &_inventory;
}
void Player::setHealth(int _health)
{
	health = _health;
}
void Player::setMaxHealth(int _maxHealth)
{
	maxHealth = _maxHealth;
}
void Player::setAlive(bool _alive)
{
	alive = _alive;
}
void Player::setStatusEffect(int _statusEffect)
{
	statusEffect = _statusEffect;
}
void Player::setStatusEffectHitChance(int _statusEffectHitChance)
{
	statusEffectHitChance = _statusEffectHitChance;
}

// Accessor Functions -- Functions that will return values of private functions
std::string Player::getName()
{
	return name;
}
Inventory* Player::getInventory()
{
	return inventory;
}
int Player::getHealth()
{
	return health;
}
int Player::getMaxHealth()
{
	return maxHealth;
}
bool Player::getAlive()
{
	return alive;
}
int Player::getStatusEffect()
{
	return statusEffect;
}
int Player::getStatusEffectHitChance()
{
	return statusEffectHitChance;
}

// Prints all of the player's attributes to the screen - mainly for testing.
void Player::printPlayerInfo(GameUI console)
{
	// Text messages for the user
	std::string extraNewline = "\n";
	std::string playerInfo = "Player's information includes:\n\n";
	std::string playerName = "Player Name: " + name + "\n\n";

	// Show player's name
	console.writeOutput(playerInfo);
	console.writeOutput(playerName);

	// Show the player's inventory
	inventory->displayItemInventory(console, "Player");

	// Show the player's health
	console.writeOutput(extraNewline);
	displayBothHealth(console);
}

// Lets the player heal from an item
void Player::useHealthItem(GameUI console, std::string item)
{
	// Text messages for the user
	std::string extraNewline = "\n";
	std::string deleteMessage = "You are now consuming a " + item + "\n";
	std::string errorMessage = "That item is not in the player's inventory.\n"
		"Please try searching around for the item.\n";

	// If the item is in the players's inventory, then continue with consuming it
	if (inventory->searchItemInventory(item) == true)
	{
		// Display that the item is being used
		console.writeOutput(deleteMessage);

		// Get the item from the player's inventory
		Item* itemPointer = inventory->getItem(console, item);

		// Get the health of the item
		int itemHealth = itemPointer->getHealing();

		// Add the health to the player's total
		changeHealth(console, itemHealth);

		// Show the player's new health to the user
		console.writeOutput(extraNewline);
		displayHealth(console);

		// Remove the item from the room's inventory
		inventory->removeItem(console, item);

		// Display the player's inventory now that the item as been used
		console.writeOutput(extraNewline);
		inventory->displayItemInventory(console, "Player");
	}
	else
	{
		// Display the item is not in the inventory
		console.writeOutput(errorMessage);
	}
}

// Change the player's health value
void Player::changeHealth(GameUI console, int _health)
{
	// Text message to the user
	std::string healthMessage = "\nUsing this item has caused your health to exceed the max health allowed to the player.\n"
		"The player's health will be set to " + std::to_string(getMaxHealth()) + ".\n";

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

// Print the player's health to the screen
void Player::displayHealth(GameUI console)
{
	// Current health of player
	std::string playersHealth = getName() + "'s Health: " + std::to_string(getHealth()) + ".\n";
	std::string playersMaxHealth = getName() + "'s Max Health: " + std::to_string(getMaxHealth()) + ".\n";

	// Display both health and max health if the player's current health is not at max health
	if (health < maxHealth)
	{
		// Display both healths
		console.writeOutput(playersHealth);
		console.writeOutput(playersMaxHealth);
	}
	else
	{
		// Display only health of the player
		console.writeOutput(playersHealth);
	}
}

// Print the player's health and max health to the screen
void Player::displayBothHealth(GameUI console)
{
	// Current health of player
	std::string playersHealth = getName() + "'s Health: " + std::to_string(getHealth()) + ".\n";
	std::string playersMaxHealth = getName() + "'s Max Health: " + std::to_string(getMaxHealth()) + ".\n";

	// Display both healths
	console.writeOutput(playersHealth);
	console.writeOutput(playersMaxHealth);
}

// Turns the player's alive variable to false - meaning they were killed.
void Player::kill()
{
	alive = false;
}