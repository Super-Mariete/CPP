#ifndef CLAPTRAP_HPP
# define CLAPTRAP_HPP

# include <iostream>

class ClapTrap
{
    protected:

    std::string name;
    int hitPoints;
    int energyPoints;
    int attackDamage;

    //Protected constructor for derived classes
    ClapTrap(const std::string& name, int hp, int energy, int damage);

    public:
    //OCF
    ClapTrap();
    ClapTrap(const ClapTrap& other);
    ClapTrap& operator=(const ClapTrap& other);
    virtual ~ClapTrap();                        //virtual destructor

    //additional constructor
    ClapTrap(const std::string& name);

    void attack(const std::string& target);
    void takeDamage(unsigned int amount);
    void beRepaired(unsigned int amount);
};

#endif