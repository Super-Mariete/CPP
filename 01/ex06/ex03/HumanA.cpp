/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   HumanA.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marta <marta@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/17 00:00:00 by marta             #+#    #+#             */
/*   Updated: 2025/10/17 00:00:00 by marta            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "HumanA.hpp"

// Constructor - MUST initialize reference in initialization list
HumanA::HumanA(std::string name, Weapon& weapon) : name(name), weapon(weapon)
{
}

// Destructor
HumanA::~HumanA(void)
{
}

// Attack function
void HumanA::attack(void) const
{
	std::cout << this->name << " attacks with their "
			  << this->weapon.getType() << std::endl;
}
