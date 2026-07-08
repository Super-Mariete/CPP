/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvigara- <mvigara-@student.42school.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/24 12:30:00 by mvigara-          #+#    #+#             */
/*   Updated: 2025/11/24 12:30:00 by mvigara-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ClapTrap.hpp"
#include "ScavTrap.hpp"
#include <iostream>

void printSeparator(const std::string& title)
{
    std::cout << "\n========== " << title << " ==========\n" << std::endl;
}

int main()
{
    printSeparator("TEST 1: Construction Chaining");
    std::cout << "Creating ClapTrap:" << std::endl;
    ClapTrap clap("Clappy");
    std::cout << "\nCreating ScavTrap (watch the chain!):" << std::endl;
    ScavTrap scav("Scavvy");

    printSeparator("TEST 2: ScavTrap Attack (different from ClapTrap)");
    clap.attack("Bandit");
    scav.attack("Psycho");

    printSeparator("TEST 3: ScavTrap Special Ability");
    scav.guardGate();

    printSeparator("TEST 4: Taking Damage");
    scav.takeDamage(30);
    scav.takeDamage(50);

    printSeparator("TEST 5: Repairing");
    scav.beRepaired(20);
    scav.beRepaired(10);

    printSeparator("TEST 6: Energy Depletion Test");
    ScavTrap energetic("Energetic");
    for(int i = 1; i <= 51; i++)
    {
        std::cout << "Action " << i << ": ";
        if(i <= 25)
            energetic.attack("Enemy");
        else
            energetic.beRepaired(1);
    }
    std::cout << "\nTrying action 51 (should fail - no energy):" << std::endl;
    energetic.attack("Ghost");

    printSeparator("TEST 7: Death Test");
    ScavTrap mortal("Mortal");
    mortal.takeDamage(50);
    mortal.takeDamage(60);  // Dies here
    mortal.attack("Ghost");  // Should fail - dead
    mortal.beRepaired(10);   // Should fail - dead

    printSeparator("TEST 8: Copy Constructor");
    ScavTrap original("Original");
    original.takeDamage(20);
    ScavTrap copy(original);
    copy.attack("Test");
    copy.guardGate();

    printSeparator("TEST 9: Assignment Operator");
    ScavTrap first("First");
    ScavTrap second("Second");
    first.takeDamage(30);
    second = first;
    second.attack("Test");
    second.guardGate();

    printSeparator("Destruction (watch the order - reverse of construction!)");
    // All objects will be destroyed here

    return 0;
}
