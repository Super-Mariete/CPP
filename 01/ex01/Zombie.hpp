#ifndef ZOMBIE_HPP
# define ZOMBIE_HPP

# include <string>
# include <iostream>

class Zombie
{
private:
	std::string	name;

public:
	Zombie(void);
	~Zombie(void);

	void	setName(std::string name);
	void	announce(void);
};

// Function prototype
Zombie*	zombieHorde(int N, std::string name);

#endif
