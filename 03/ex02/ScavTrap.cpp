/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ScavTrap.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvigara- <mvigara-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/04 20:08:43 by mvigara-          #+#    #+#             */
/*   Updated: 2025/11/04 20:56:36 by mvigara-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ScavTrap.hpp"

// Constructor por defecto
ScavTrap::ScavTrap() : ClapTrap("", 100, 50, 20)
{
    std::cout << "ScavTrap: Created! Let's go scavenging!" << std::endl;
}

ScavTrap::ScavTrap(const std::string& name) : ClapTrap(name, 100, 50, 20)
{
    std::cout << "ScavTrap " << this->name << " spawned! It's showtime!" << std::endl;
}

ScavTrap::ScavTrap(const ScavTrap& other) : ClapTrap(other)
{
    std::cout << "ScavTrap " << this->name << " has been cloned! Back in action!" << std::endl;
}

ScavTrap& ScavTrap::operator=(const ScavTrap& other)
{
    ClapTrap::operator=(other);
    std::cout << "ScavTrap " << this->name << " assignment complete. Let's reboot!" << std::endl;
    return *this;
}

ScavTrap::~ScavTrap()
{
    std::cout << "ScavTrap " << this->name << " shutting down... Bye!" << std::endl;
}

void ScavTrap::attack(const std::string& target)
{
    if(energyPoints <= 0 || hitPoints <= 0)
    {
        std::cout << "ScavTrap " << this->name << " can't attack! Check systems or health." << std::endl;
        return;
    }
    std::cout << "ScavTrap " << this->name << " fiercely attacks " << target << ", causing "
        << attackDamage << " damage!" << std::endl;
    energyPoints--;
}

void ScavTrap::guardGate()
{
    std::cout << "ScavTrap " << this->name << " is now in Gate Keeper mode!" << std::endl;
}
