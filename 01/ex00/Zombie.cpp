#include "Zombie.hpp"

// Constructor
Zombie::Zombie(std::string name) : name(name)
{
	std::cout << this->name << " is born" << std::endl;
}

// Destructor
Zombie::~Zombie(void)
{
	std::cout << this->name << " is destroyed" << std::endl;
}

// Announce function
void Zombie::announce(void)
{
	std::cout << this->name << ": BraiiiiiiinnnzzzZ..." << std::endl;
}
