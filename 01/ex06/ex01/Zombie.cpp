/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Zombie.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marta <marta@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/17 00:00:00 by marta             #+#    #+#             */
/*   Updated: 2025/10/17 00:00:00 by marta            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Zombie.hpp"

// Default constructor (needed for array allocation)
Zombie::Zombie(void) : name("Unnamed")
{
}

// Destructor
Zombie::~Zombie(void)
{
	std::cout << this->name << " is destroyed" << std::endl;
}

// Set zombie name
void Zombie::setName(std::string name)
{
	this->name = name;
}

// Announce function
void Zombie::announce(void)
{
	std::cout << this->name << ": BraiiiiiiinnnzzzZ..." << std::endl;
}
