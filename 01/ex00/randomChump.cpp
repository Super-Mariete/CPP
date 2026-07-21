#include "Zombie.hpp"

// Creates a zombie on the STACK (automatic allocation)
// Automatically destroyed when function ends
// Use when: zombie only needed within function scope
void randomChump(std::string name)
{
	Zombie zombie(name);
	zombie.announce();
}
