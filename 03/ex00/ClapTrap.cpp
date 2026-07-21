#include "ClapTrap.hpp"

//Constructor ClapTrap() por defecto inicializar name = ?, hitPoints = 10, energyPoints = 10, attackDamage = 0
ClapTrap::ClapTrap() : name(""), hitPoints(10), energyPoints(10), attackDamage(0)
{
    std::cout << "ClapTrap: Activating! Ready to serve! *beep boop*" << std::endl;
}

// Constructor con nombre específico
ClapTrap::ClapTrap(const std::string& name) : name(name), hitPoints(10), energyPoints(10), attackDamage(0)
{
    std::cout << "ClapTrap " << this->name << " online! Let's get this party started!" << std::endl;
}
//Copy Constructor
ClapTrap::ClapTrap(const ClapTrap& other) : name(other.name),
                                            hitPoints(other.hitPoints),
                                            energyPoints(other.energyPoints),
                                            attackDamage(other.attackDamage)
{
    std::cout << "ClapTrap " << this->name << " cloned! Two is better than one, right?" << std::endl;
}

//copy asignment operator
ClapTrap& ClapTrap::operator=(const ClapTrap& other)
{
    std::cout << "ClapTrap copying data... Syncing... Done! I think?" << std::endl;
    if (this != &other)
    {
        this->name = other.name;
        this->attackDamage = other.attackDamage;
        this->energyPoints = other.energyPoints;
        this->hitPoints = other.hitPoints;
    }
    return *this;
}

//destuctor
ClapTrap::~ClapTrap()
{
    std::cout << "ClapTrap " << this->name << " shutting down... I'll miss you! *sad beep*" << std::endl;
}

//methods attack; takeDamage ; beRepaired();
void ClapTrap::takeDamage(unsigned int amount)
{
    this->hitPoints = (amount >= static_cast<unsigned int>(this->hitPoints)) ? 0 : this->hitPoints - amount;
    if(this->hitPoints <= 0)
        std::cout << "ClapTrap " << this->name << " is dead! Argh arghargh death gurgle gurglegurgle!" << std::endl;
    else
        std::cout << "ClapTrap " << this->name << " took " << amount << " damage! Ouch! That hurt!" << std::endl;
}

void ClapTrap::beRepaired(unsigned int amount)
{
    if(this->energyPoints <= 0 || this->hitPoints <= 0)
    {
        std::cout << "ClapTrap " << this->name << " can't repair! Out of juice... or dead... or both!" << std::endl;
        return;
    }
    else{
        this->hitPoints += amount;
        this->energyPoints--;
        std::cout << "ClapTrap " << this->name << " repairs itself for " << amount << " HP! Good as new! Well... almost!" << std::endl;
    }

}

void ClapTrap::attack(const std::string& target)
{
    if(this->energyPoints <= 0 || this->hitPoints <= 0)
    {
        std::cout << "ClapTrap " << this->name << " wants to attack but can't! Too tired... or dead!" << std::endl;
        return;
    }
    else{
        std::cout << "ClapTrap " << this->name << " attacks " << target << ", causing "
            << this->attackDamage << " points of damage!" << std::endl;
        this->energyPoints--;
    }
}
