#include "Item.h"

// Constructors
Item::Item()
{
	name = "";
	healing = 0;
}
Item::Item(std::string _name, int _healing)
{
	name = _name;
	healing = _healing;
}

// Mutator Functions -- Functions that will be allowed to change private variables
void Item::setName(std::string _name)
{
	name = _name;
}
void Item::setHealing(int _healing)
{
	healing = _healing;
}

// Accessor Functions -- Functions that will return values of private functions
std::string Item::getName()
{
	return name;
}
int Item::getHealing()
{
	return healing;
}