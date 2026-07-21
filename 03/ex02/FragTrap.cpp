#include "FragTrap.hpp"

// Constructor por defecto
// Hit points (100), Energy points (100), Attack damage (30)
FragTrap::FragTrap() : ClapTrap("", 100, 100, 30)
{
    std::cout << "FragTrap: Default constructor activated! Ready to frag!" << std::endl;
}

// Constructor with name
FragTrap::FragTrap(const std::string& name) : ClapTrap(name, 100, 100, 30)
{
    std::cout << "FragTrap " << this->name << " constructed! Time to get some frags!" << std::endl;
}

// Copy constructor
FragTrap::FragTrap(const FragTrap& other) : ClapTrap(other)
{
    std::cout << "FragTrap " << this->name << " copied! Double the frags!" << std::endl;
}

// Assignment operator
FragTrap& FragTrap::operator=(const FragTrap& other)
{
    ClapTrap::operator=(other);
    std::cout << "FragTrap " << this->name << " assigned! Synced and ready!" << std::endl;
    return *this;
}

// Destructor
FragTrap::~FragTrap()
{
    std::cout << "FragTrap " << this->name << " destroyed! GG!" << std::endl;
}

// Special ability
void FragTrap::highFivesGuys(void)
{
    std::cout << "FragTrap " << this->name << " says: High fives, guys! ✋" << std::endl;
}
