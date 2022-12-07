#include "Inventory.h"

// Null constructor
Inventory::Inventory()
{
	// Null constructor
}

// Returns the size of the itemInventory
int Inventory::getItemInventorySize()
{
	return itemInventory.size();
}

// Adds an item object to the item inventory list
void Inventory::addItem(Item& _item)
{
	// Add the item to the item inventory
	itemInventory.push_back(&_item);
}

// Adds an attack object to the attack inventory
void Inventory::addAttack(GameUI console, Attack& _attack)
{
	// Error message
	std::string errorMessage = "The player already has 4 attacks, which is the maximum amount of attacks allowed.\n"
							   "Drop an attack before trying to pick one up you useless being.\n";

	// If the attack inventory has less than 4 attacks, add this attack
	if (attackInventory.size() < 4)
	{
		// Add the attack to the attack inventory
		attackInventory.push_back(&_attack);
	}
	else
	{
		// Tell the user that they can't pickup the attack because they already have 4 attacks
		console.writeOutput(errorMessage);
	}
}

// Returns a pointer to the address of the specified item
Item* Inventory::getItem(GameUI console, std::string item)
{
	// Error message
	std::string errorMessage = "That item is not in the item inventory, it can not be deleted.\n";

	// Iterator that can be used to go through a list that holds pointers to item objects
	std::list<Item*>::iterator itr;

	// An Item pointer that can get the item the iterator is pointing to
	Item* itemPointer;

	// Make sure the item is in the inventory before trying to return it
	if (searchItemInventory(item))
	{
		// Iterate through all of the items in the list
		for (itr = itemInventory.begin(); itr != itemInventory.end(); ++itr)
		{
			// Get the item the iterator is pointing too
			itemPointer = *itr;

			// Return a pointer to the item object
			if (itemPointer->getName() == item)
			{
				return itemPointer;
			}
		}
	}
	else
	{
		// Display that the item is not in the inventory
		console.writeOutput(errorMessage);
	}
}

// Function to get the only attack a monster has
Attack* Inventory::getAttack(GameUI console)
{
	// Error message
	std::string errorMessage = "There are no attacks to get.\n";

	// Iterator that can be used to go through a list that holds pointers to item objects
	std::list<Attack*>::iterator itr;

	// An Item pointer that can get the item the iterator is pointing to
	Attack* attackPointer;

	// Formallity check to make sure the monster has an attack
	if (attackInventory.size() != 0)
	{
		// Return the only attack in the list - this is for monsters only
		for (itr = attackInventory.begin(); itr != attackInventory.end(); ++itr)
		{
			// Return the attack
			return *itr;
		}
	}
	else
	{
		// Display that the item is not in the inventory
		console.writeOutput(errorMessage);
	}
}

// Returns the attack object that is being specified for
Attack* Inventory::getAttack(GameUI console, std::string attack)
{
	// Error message
	std::string errorMessage = "That attack is not in the attack inventory, it can not be deleted.\n";

	// Iterator that can be used to go through a list that holds pointers to attack objects
	std::list<Attack*>::iterator itr;

	// An attack pointer that can get the item the iterator is pointing to
	Attack* attackPointer;

	// Make sure the attack is in the inventory before trying to return it
	if (searchAttackInventory(attack))
	{
		// Iterate through all of the attacks in the list
		for (itr = attackInventory.begin(); itr != attackInventory.end(); ++itr)
		{
			// Get the attack the iterator is pointing too
			attackPointer = *itr;

			// Get the correct attack object
			if (attackPointer->getName() == attack)
			{
				// Return the attack pointer
				return attackPointer;
			}
		}
	}
	else
	{
		// Display that the attack is not in the inventory
		console.writeOutput(errorMessage);
	}
}

// Displays all of the items in the item inventory
void Inventory::displayItemInventory(GameUI console, std::string _type)
{
	// Strings that will be passed to the console and printed out
	std::string promptMessage = _type + "'s Item Inventory:\n";
	std::string errorMessage = "No items.\n";
	std::string itemName;

	// Iterator that can be used to go through a list that holds pointers to item objects
	std::list<Item*>::iterator itr;

	// An Item pointer that can get the item the iterator is pointing to
	Item* itemPointer;

	// Header text
	console.writeOutput(promptMessage);

	// Display an error message if there are no items in the list
	if (itemInventory.size() != 0)
	{
		// Print all of the names of the items in the list
		for (itr = itemInventory.begin(); itr != itemInventory.end(); ++itr)
		{
			// Get the item the iterator is pointing too
			itemPointer = *itr;

			// Get the name of the item and print it to the screen
			itemName = "-" + itemPointer->getName() + ".\n";
			console.writeOutput(itemName);
		}
	}
	else
	{
		// Display that there are no items currently in the list
		console.writeOutput(errorMessage);
	}
}

// Displays all of the attacks in the attack inventory
void Inventory::displayAttackInventory(GameUI console, std::string _type)
{
	// Strings that will be passed to the console and printed out
	std::string extraNewline = "\n";
	std::string promptMessage = _type + "'s Attack Inventory:\n";
	std::string errorMessage = "No items.\n";

	// Iterator that can be used to go through a list that holds pointers to attack objects
	std::list<Attack*>::iterator itr;

	// An attack pointer that can get the attack the iterator is pointing to
	Attack* attackPointer;

	// Header text
	console.writeOutput(promptMessage);

	// Display an error message if there are no attacks in the list
	if (attackInventory.size() != 0)
	{
		// Print all of the names of the attacks in the list
		for (itr = attackInventory.begin(); itr != attackInventory.end(); ++itr)
		{
			// Get the item the iterator is pointing too
			attackPointer = *itr;

			// Display the attack name
			console.writeOutput("-");
			attackPointer->displayAttack(console);
			console.writeOutput(extraNewline);
		}
	}
	else
	{
		// Display that there are no attacks currently in the list
		console.writeOutput(errorMessage);
	}
}

// Remove an item from the item inventory
void Inventory::removeItem(GameUI console, std::string item)
{
	// Error message
	std::string errorMessage = "That item is not in the item inventory, it cannot be deleted.\n";

	// Iterator that can be used to go through a list that holds pointers to item objects
	std::list<Item*>::iterator itr;

	// An Item pointer that can get the item the iterator is pointing to
	Item* itemPointer;

	// Make sure the item is in the inventory before trying to remove it
	if (searchItemInventory(item))
	{
		// Iterate through all of the items in the list
		for (itr = itemInventory.begin(); itr != itemInventory.end(); ++itr)
		{
			// Get the item the iterator is pointing too
			itemPointer = *itr;

			// Get the correct item to delete
			if (itemPointer->getName() == item)
			{
				// Delete the item
				itr = itemInventory.erase(itr);
				break;
			}
		}
	}
	else
	{
		// Display that the item is not in the inventory
		console.writeOutput(errorMessage);
	}
}

// Remove an attack from the attack inventory
void Inventory::removeAttack(GameUI console, std::string attack)
{
	// Error message
	std::string errorMessage = "That attack is not in the attack inventory, it cannot be deleted.\n";

	// Iterator that can be used to go through a list that holds pointers to attack objects
	std::list<Attack*>::iterator itr;

	// An attack pointer that can get the attack the iterator is pointing to
	Attack* attackPointer;

	// Make sure the attack is in the inventory before trying to remove it
	if (searchAttackInventory(attack))
	{
		// Iterate through all of the attacks in the list
		for (itr = attackInventory.begin(); itr != attackInventory.end(); ++itr)
		{
			// Get the attacks the iterator is pointing too
			attackPointer = *itr;

			// Get the correct attack to delete
			if (attackPointer->getName() == attack)
			{
				// Delete the attack
				itr = attackInventory.erase(itr);
				break;
			}
		}
	}
	else
	{
		// Display that the attack is not in the inventory
		console.writeOutput(errorMessage);
	}
}

// Searches the item inventory list and returns true or false based on
// if the item was found or not
bool Inventory::searchItemInventory(std::string item)
{
	// Iterator that can be used to go through a list that holds pointers to item objects
	std::list<Item*>::iterator itr;

	// An Item pointer that can get the item the iterator is pointing to
	Item* itemPointer;

	// Iterate through all of the items in the list
	for (itr = itemInventory.begin(); itr != itemInventory.end(); ++itr)
	{
		// Get the item the iterator is pointing too
		itemPointer = *itr;

		// Return true if the item is in the list
		if (itemPointer->getName() == item)
		{
			// Item is in the list, return true
			return true;
		}
	}

	// Return false if the item is not in the list
	return false;
}

// Searches the attack inventory list and returns true or false based on
// if the attack was found or not
bool Inventory::searchAttackInventory(std::string attack)
{
	// Iterator that can be used to go through a list that holds pointers to attack objects
	std::list<Attack*>::iterator itr;

	// An attack pointer that can get the attack the iterator is pointing to
	Attack* attackPointer;

	// Iterate through all of the attacks in the list
	for (itr = attackInventory.begin(); itr != attackInventory.end(); ++itr)
	{
		// Get the attack the iterator is pointing too
		attackPointer = *itr;

		// Return true if the attack is in the list
		if (attackPointer->getName() == attack)
		{
			// Attack is in the list, return true
			return true;
		}
	}

	// Return false if the item is not in the list
	return false;
}

// Returns the size of the attack inventory
int Inventory::getAttackInventorySize()
{
	// Return size of attack inventory
	return attackInventory.size();
}