#include "Zombie.hpp"

// Creates a zombie on the HEAP (dynamic allocation)
// Must be deleted manually with 'delete'
// Use when: zombie needs to exist beyond function scope
Zombie* newZombie(std::string name)
{
	return new Zombie(name);
}
