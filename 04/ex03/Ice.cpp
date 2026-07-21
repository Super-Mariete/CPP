#include "Ice.hpp"
#include <iostream>

Ice::Ice() : AMateria("ice")
{
}

Ice::Ice(Ice const & src) : AMateria(src)
{
}

Ice::~Ice()
{
}

Ice & Ice::operator=(Ice const & rhs)
{
    if (this != &rhs)
        AMateria::operator=(rhs);
    return *this;
}

AMateria* Ice::clone() const
{
    return new Ice(*this);
}

void Ice::use(ICharacter& target)
{
    std::cout << "* shoots an ice bolt at " << target.getName() << " *" << std::endl;
}
