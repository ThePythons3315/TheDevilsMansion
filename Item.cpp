#include "Item.h"

// Constructors
Item::Item()
{
	name = "";
	healing = 0;
	statusEffect = 0;
}
Item::Item(std::string _name, std::string _description, int _healing, int _statusEffect)
{
	name = _name;
	healing = _healing;
	statusEffect = _statusEffect;
	description = _description;
}

// Mutator Functions -- Functions that will be allowed to change private variables
void Item::setName(std::string _name)
{
	name = _name;
}
void Item::setDescritpion(std::string _description)
{
	description = _description;
}
void Item::setHealing(int _healing)
{
	healing = _healing;
}
void Item::setStatusEffect(int _statusEffect)
{
	statusEffect = _statusEffect;
}


// Accessor Functions -- Functions that will return values of private functions
std::string Item::getName()
{
	return name;
}
std::string Item::getDescription()
{
	return description;
}
int Item::getHealing()
{
	return healing;
}
int Item::getStatusEffect()
{
	return statusEffect;
}

// Shows the items attributes
void Item::viewItemDescription(GameUI console)
{
	// Text messages for the user
	std::string outputName= "Item Name: " + name + ":\n";
	std::string outputDescription = "-" + description + "\n";

	// Display the messages about the item
	console.writeOutput(outputName);
	console.writeOutput(outputDescription);
}
