/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvigara- <mvigara-@student.42school.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/24 12:50:00 by mvigara-          #+#    #+#             */
/*   Updated: 2025/11/24 12:50:00 by mvigara-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ClapTrap.hpp"
#include "ScavTrap.hpp"
#include "FragTrap.hpp"
#include <iostream>

void printSeparator(const std::string& title)
{
    std::cout << "\n========== " << title << " ==========\n" << std::endl;
}

int main()
{
    printSeparator("TEST 1: Construction Chaining (all three types)");
    std::cout << "Creating ClapTrap:" << std::endl;
    ClapTrap clap("Clappy");
    std::cout << "\nCreating ScavTrap:" << std::endl;
    ScavTrap scav("Scavvy");
    std::cout << "\nCreating FragTrap (watch the chain!):" << std::endl;
    FragTrap frag("Fraggy");

    printSeparator("TEST 2: Different Attacks");
    clap.attack("Target1");  // 0 damage
    scav.attack("Target2");  // 20 damage
    frag.attack("Target3");  // 30 damage

    printSeparator("TEST 3: FragTrap Special Ability");
    frag.highFivesGuys();

    printSeparator("TEST 4: Taking Damage");
    frag.takeDamage(40);
    frag.takeDamage(30);

    printSeparator("TEST 5: Repairing");
    frag.beRepaired(25);
    frag.beRepaired(15);

    printSeparator("TEST 6: Energy Capacity Test (FragTrap has 100)");
    FragTrap energetic("Energetic");
    std::cout << "Performing 50 attacks (FragTrap has 100 energy):" << std::endl;
    for(int i = 1; i <= 50; i++)
    {
        energetic.attack("Enemy");
    }
    std::cout << "\nPerforming 50 repairs (should use up remaining 50 energy):" << std::endl;
    for(int i = 1; i <= 50; i++)
    {
        energetic.beRepaired(1);
    }
    std::cout << "\nTrying action 101 (should fail - no energy):" << std::endl;
    energetic.attack("Ghost");
    energetic.highFivesGuys();  // This should still work (doesn't use energy)

    printSeparator("TEST 7: Death Test");
    FragTrap mortal("Mortal");
    mortal.takeDamage(60);
    mortal.takeDamage(50);  // Dies here
    mortal.attack("Ghost");  // Should fail - dead
    mortal.beRepaired(10);   // Should fail - dead
    mortal.highFivesGuys();  // Can still say hi even when dead!

    printSeparator("TEST 8: Copy Constructor");
    FragTrap original("Original");
    original.takeDamage(30);
    FragTrap copy(original);
    copy.attack("Test");
    copy.highFivesGuys();

    printSeparator("TEST 9: Assignment Operator");
    FragTrap first("First");
    FragTrap second("Second");
    first.takeDamage(40);
    second = first;
    second.attack("Test");
    second.highFivesGuys();

    printSeparator("TEST 10: All special abilities");
    scav.guardGate();
    frag.highFivesGuys();

    printSeparator("Destruction (watch the order - reverse of construction!)");
    // All objects will be destroyed here

    return 0;
}
