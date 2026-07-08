/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   DiamondTrap.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvigara- <mvigara-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/24 13:00:00 by mvigara-          #+#    #+#             */
/*   Updated: 2025/11/24 13:00:00 by mvigara-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "DiamondTrap.hpp"

// Default constructor
// Hit points (FragTrap: 100)
// Energy points (ScavTrap: 50)
// Attack damage (FragTrap: 30)
DiamondTrap::DiamondTrap() : ClapTrap("_clap_name", 100, 50, 30), ScavTrap(), FragTrap(), name("")
{
    std::cout << "DiamondTrap: Default constructor called!" << std::endl;
}

// Constructor with name
// ClapTrap::name will be name + "_clap_name"
// DiamondTrap::name will be the parameter
DiamondTrap::DiamondTrap(const std::string& name)
    : ClapTrap(name + "_clap_name", 100, 50, 30), ScavTrap(), FragTrap(), name(name)
{
    std::cout << "DiamondTrap " << this->name << " constructed! A perfect hybrid!" << std::endl;
}

// Copy constructor
DiamondTrap::DiamondTrap(const DiamondTrap& other)
    : ClapTrap(other), ScavTrap(other), FragTrap(other), name(other.name)
{
    std::cout << "DiamondTrap " << this->name << " copied! Cloning the hybrid!" << std::endl;
}

// Assignment operator
DiamondTrap& DiamondTrap::operator=(const DiamondTrap& other)
{
    if (this != &other)
    {
        ClapTrap::operator=(other);
        ScavTrap::operator=(other);
        FragTrap::operator=(other);
        this->name = other.name;
    }
    std::cout << "DiamondTrap " << this->name << " assigned! Syncing hybrid data!" << std::endl;
    return *this;
}

// Destructor
DiamondTrap::~DiamondTrap()
{
    std::cout << "DiamondTrap " << this->name << " destroyed! The hybrid is no more!" << std::endl;
}

// Special ability
void DiamondTrap::whoAmI()
{
    std::cout << "I am DiamondTrap " << this->name
              << " and my ClapTrap name is " << ClapTrap::name << std::endl;
}
