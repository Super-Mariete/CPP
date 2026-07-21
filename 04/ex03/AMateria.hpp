#ifndef AMATERIA_HPP
#define AMATERIA_HPP

#include <string>

class ICharacter;

class AMateria
{
protected:
    std::string _type;

public:
    AMateria(std::string const & type);
    AMateria(AMateria const & src);
    virtual ~AMateria();

    AMateria & operator=(AMateria const & rhs);

    std::string const & getType() const;

    virtual AMateria* clone() const = 0;
    virtual void use(ICharacter& target);
};

#endif
