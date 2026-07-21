#include "Weapon.hpp"

// Constructor
Weapon::Weapon(std::string type) : type(type)
{
}

// Destructor
Weapon::~Weapon(void)
{
}

// Returns a const reference to type (no copy, read-only)
const std::string& Weapon::getType(void) const
{
	return this->type;
}

// Sets the weapon type
void Weapon::setType(std::string type)
{
	this->type = type;
}
