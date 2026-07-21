#include "HumanA.hpp"

// Constructor - MUST initialize reference in initialization list
HumanA::HumanA(std::string name, Weapon& weapon) : name(name), weapon(weapon)
{
}

// Destructor
HumanA::~HumanA(void)
{
}

// Attack function
void HumanA::attack(void) const
{
	std::cout << this->name << " attacks with their "
			  << this->weapon.getType() << std::endl;
}
