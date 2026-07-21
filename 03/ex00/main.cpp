#include "ClapTrap.hpp"
#include <iostream>

void printSeparator(const std::string& title)
{
    std::cout << "\n========== " << title << " ==========\n" << std::endl;
}

int main()
{
    printSeparator("TEST 1: Basic Construction");
    ClapTrap robot1;
    ClapTrap robot2("Clappy");

    printSeparator("TEST 2: Basic Attack");
    robot2.attack("Bandit");
    robot2.attack("Psycho");

    printSeparator("TEST 3: Taking Damage");
    robot2.takeDamage(3);
    robot2.takeDamage(5);

    printSeparator("TEST 4: Repairing");
    robot2.beRepaired(4);
    robot2.beRepaired(2);

    printSeparator("TEST 5: Energy Depletion");
    ClapTrap robot3("Energetic");
    robot3.attack("Enemy1");
    robot3.attack("Enemy2");
    robot3.attack("Enemy3");
    robot3.beRepaired(2);
    robot3.attack("Enemy4");
    robot3.attack("Enemy5");
    robot3.attack("Enemy6");
    robot3.attack("Enemy7");
    robot3.attack("Enemy8");
    robot3.attack("Enemy9");
    robot3.attack("Enemy10");
    // Now out of energy (10 actions done)
    robot3.attack("Enemy11");      // Should fail - no energy
    robot3.beRepaired(5);           // Should fail - no energy

    printSeparator("TEST 6: Death");
    ClapTrap robot4("Fragile");
    robot4.takeDamage(5);
    robot4.takeDamage(10);  // Dies here (5 + 10 > 10 HP)
    robot4.attack("Ghost");  // Should fail - dead
    robot4.beRepaired(5);    // Should fail - dead

    printSeparator("TEST 7: Copy Constructor");
    ClapTrap robot5("Original");
    robot5.takeDamage(3);
    ClapTrap robot6(robot5);  // Copy constructor
    robot6.attack("Test");

    printSeparator("TEST 8: Assignment Operator");
    ClapTrap robot7("First");
    ClapTrap robot8("Second");
    robot7.takeDamage(2);
    robot8 = robot7;  // Assignment operator
    robot8.attack("Test");

    printSeparator("TEST 9: Massive Damage (Overkill)");
    ClapTrap robot9("Tank");
    robot9.takeDamage(100);  // Way more than 10 HP - should clamp to 0

    printSeparator("Destructors (watch the order!)");
    // All robots will be destroyed here when main ends

    return 0;
}
