#ifndef HUMANB_HPP
# define HUMANB_HPP

# include "Weapon.hpp"
# include <iostream>

class HumanB
{
private:
	std::string	name;
	Weapon*		weapon;  // Pointer: may or may NOT have a weapon

public:
	HumanB(std::string name);
	~HumanB(void);

	void	setWeapon(Weapon& weapon);
	void	attack(void) const;
};

#endif
