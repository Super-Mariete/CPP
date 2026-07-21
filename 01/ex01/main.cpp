#include "Zombie.hpp"

int main(void)
{
	int N = 5;

	std::cout << "=== Creating a horde of " << N << " zombies ===" << std::endl;
	Zombie* horde = zombieHorde(N, "HordeZombie");

	if (!horde)
	{
		std::cout << "Failed to create horde" << std::endl;
		return 1;
	}

	std::cout << "\n=== Zombies announcing ===" << std::endl;
	for (int i = 0; i < N; i++)
		horde[i].announce();

	std::cout << "\n=== Deleting horde ===" << std::endl;
	delete[] horde; // Must use delete[] for arrays!

	return 0;
}
