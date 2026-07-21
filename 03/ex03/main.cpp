#include "ClapTrap.hpp"
#include "ScavTrap.hpp"
#include "FragTrap.hpp"
#include "DiamondTrap.hpp"
#include <iostream>

void printSeparator(const std::string& title)
{
    std::cout << "\n========== " << title << " ==========\n" << std::endl;
}

int main()
{
    printSeparator("TEST 1: DiamondTrap Construction (watch the chain!)");
    DiamondTrap diamond("Diamond");

    printSeparator("TEST 2: whoAmI() - showing both names");
    diamond.whoAmI();

    printSeparator("TEST 3: Attack (should use ScavTrap's attack)");
    diamond.attack("Target");

    printSeparator("TEST 4: Verify stats");
    std::cout << "Testing HP (should be 100 from FragTrap):" << std::endl;
    diamond.takeDamage(50);
    std::cout << "\nTesting energy (should be 50 from ScavTrap):" << std::endl;
    for(int i = 0; i < 51; i++)
        diamond.attack("Enemy");
    std::cout << "Attack 51 should fail (no energy left)" << std::endl;

    printSeparator("TEST 5: Inherited special abilities");
    DiamondTrap diamond2("Hybrid");
    diamond2.guardGate();      // From ScavTrap
    diamond2.highFivesGuys();  // From FragTrap
    diamond2.whoAmI();         // From DiamondTrap

    printSeparator("TEST 6: Taking damage and repairing");
    diamond2.takeDamage(30);
    diamond2.beRepaired(20);
    diamond2.takeDamage(95);  // Should die

    printSeparator("TEST 7: Dead DiamondTrap");
    diamond2.attack("Ghost");
    diamond2.beRepaired(10);
    diamond2.whoAmI();  // Should still work

    printSeparator("TEST 8: Copy constructor");
    DiamondTrap original("Original");
    original.takeDamage(20);
    DiamondTrap copy(original);
    copy.whoAmI();
    copy.attack("Test");

    printSeparator("TEST 9: Assignment operator");
    DiamondTrap first("First");
    DiamondTrap second("Second");
    first.takeDamage(30);
    second = first;
    second.whoAmI();
    second.attack("Test");

    printSeparator("TEST 10: Multiple DiamondTraps");
    DiamondTrap d1("Alpha");
    DiamondTrap d2("Beta");
    DiamondTrap d3("Gamma");
    d1.whoAmI();
    d2.whoAmI();
    d3.whoAmI();

    printSeparator("Destruction (reverse order of construction)");
    // All objects will be destroyed here

    return 0;
}
