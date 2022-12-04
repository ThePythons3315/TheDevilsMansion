#include "Item.h"

// Constructors
Item::Item()
{
	name = "";
	healing = 0;
	statusEffect = 0;
}
Item::Item(std::string _name, int _healing, int _statusEffect)
{
	name = _name;
	healing = _healing;
	statusEffect = _statusEffect;
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
void Item::setStatusEffect(int _statusEffect)
{
	statusEffect = _statusEffect;
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
int Item::getStatusEffect()
{
	return statusEffect;
}
