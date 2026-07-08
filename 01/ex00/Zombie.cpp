/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Zombie.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvigara- <mvigara-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/17 12:10:26 by marta             #+#    #+#             */
/*   Updated: 2025/10/21 21:03:43 by mvigara-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Zombie.hpp"

// Constructor
Zombie::Zombie(std::string name) : name(name)
{
	std::cout << this->name << " is born" << std::endl;
}

// Destructor
Zombie::~Zombie(void)
{
	std::cout << this->name << " is destroyed" << std::endl;
}

// Announce function
void Zombie::announce(void)
{
	std::cout << this->name << ": BraiiiiiiinnnzzzZ..." << std::endl;
}
