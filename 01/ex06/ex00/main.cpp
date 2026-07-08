/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvigara- <mvigara-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/17 12:07:21 by marta             #+#    #+#             */
/*   Updated: 2025/10/21 21:02:45 by mvigara-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Zombie.hpp"

int main(void)
{
	std::cout << "=== Creating zombie on HEAP ===" << std::endl;
	Zombie* heapZombie = newZombie("HeapZombie");
	heapZombie->announce();
	std::cout << "HeapZombie still exists here..." << std::endl;
	delete heapZombie; // Must manually delete

	std::cout << "\n=== Creating zombie on STACK ===" << std::endl;
	randomChump("StackZombie");
	std::cout << "StackZombie is already destroyed here..." << std::endl;

	std::cout << "\n=== Creating multiple heap zombies ===" << std::endl;
	Zombie* z1 = newZombie("Zombie1");
	Zombie* z2 = newZombie("Zombie2");
	Zombie* z3 = newZombie("Zombie3");

	z1->announce();
	z2->announce();
	z3->announce();

	delete z1;
	delete z2;
	delete z3;

	return 0;
}
