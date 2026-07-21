#include "HumanB.hpp"

// Constructor - weapon initialized to NULL (no weapon yet)
HumanB::HumanB(std::string name) : name(name), weapon(NULL)
{
}

// Destructor
HumanB::~HumanB(void)
{
}

// Set weapon
void HumanB::setWeapon(Weapon& weapon)
{
	this->weapon = &weapon;
}

// Attack function
void HumanB::attack(void) const
{
	if (this->weapon)
		std::cout << this->name << " attacks with their "
				  << this->weapon->getType() << std::endl;
	else
		std::cout << this->name << " has no weapon!" << std::endl;
}
