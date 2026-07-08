/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   zombieHorde.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marta <marta@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/17 00:00:00 by marta             #+#    #+#             */
/*   Updated: 2025/10/17 00:00:00 by marta            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Zombie.hpp"

// Allocates N zombies in a SINGLE allocation using new[]
// Must be deleted with delete[] (not delete!)
Zombie* zombieHorde(int N, std::string name)
{
	if (N <= 0)
		return NULL;

	// Allocate array of N zombies
	Zombie* horde = new Zombie[N];

	// Initialize each zombie with the given name
	for (int i = 0; i < N; i++)
		horde[i].setName(name);

	return horde;
}
