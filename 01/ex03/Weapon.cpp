/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Weapon.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marta <marta@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/17 00:00:00 by marta             #+#    #+#             */
/*   Updated: 2025/10/17 00:00:00 by marta            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Weapon.hpp"

// Constructor
Weapon::Weapon(std::string type) : type(type)
{
}

// Destructor
Weapon::~Weapon(void)
{
}

// Returns a const reference to type (no copy, read-only)
const std::string& Weapon::getType(void) const
{
	return this->type;
}

// Sets the weapon type
void Weapon::setType(std::string type)
{
	this->type = type;
}
