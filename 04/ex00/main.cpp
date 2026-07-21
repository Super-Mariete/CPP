#include "Animal.hpp"
#include "Dog.hpp"
#include "Cat.hpp"
#include "WrongAnimal.hpp"
#include "WrongCat.hpp"

void printSeparator(const std::string& title)
{
    std::cout << "\n========== " << title << " ==========\n" << std::endl;
}

int main()
{
    printSeparator("TEST 1: Subject Tests - Polymorphism Works");
    const Animal* meta = new Animal();
    const Animal* j = new Dog();
    const Animal* i = new Cat();

    std::cout << "\nTypes:" << std::endl;
    std::cout << j->getType() << " " << std::endl;
    std::cout << i->getType() << " " << std::endl;

    std::cout << "\nSounds (polymorphism working):" << std::endl;
    i->makeSound(); //will output the cat sound!
    j->makeSound();
    meta->makeSound();

    std::cout << "\nDeleting animals:" << std::endl;
    delete meta;
    delete j;
    delete i;

    printSeparator("TEST 2: Wrong Classes - NO Polymorphism");
    const WrongAnimal* wrongMeta = new WrongAnimal();
    const WrongAnimal* wrongCat = new WrongCat();

    std::cout << "\nTypes:" << std::endl;
    std::cout << wrongCat->getType() << " " << std::endl;

    std::cout << "\nSounds (polymorphism NOT working - both output WrongAnimal sound):" << std::endl;
    wrongCat->makeSound(); // Will output WrongAnimal sound, not WrongCat!
    wrongMeta->makeSound();

    std::cout << "\nDeleting wrong animals:" << std::endl;
    delete wrongCat;
    delete wrongMeta;

    printSeparator("TEST 3: Stack vs Heap Allocation");
    std::cout << "Creating on stack:" << std::endl;
    Dog stackDog;
    Cat stackCat;

    std::cout << "\nMaking sounds:" << std::endl;
    stackDog.makeSound();
    stackCat.makeSound();

    std::cout << "\nLeaving scope (automatic destruction):" << std::endl;

    printSeparator("TEST 4: Copy Constructor and Assignment");
    std::cout << "Creating original dog:" << std::endl;
    Dog originalDog;

    std::cout << "\nCopy constructor:" << std::endl;
    Dog copiedDog(originalDog);

    std::cout << "\nAssignment operator:" << std::endl;
    Dog assignedDog;
    assignedDog = originalDog;

    std::cout << "\nAll dogs making sounds:" << std::endl;
    originalDog.makeSound();
    copiedDog.makeSound();
    assignedDog.makeSound();

    std::cout << "\nDestruction:" << std::endl;

    printSeparator("TEST 5: Array of Animals (Polymorphism)");
    const Animal* animals[4];

    std::cout << "Creating array:" << std::endl;
    animals[0] = new Dog();
    animals[1] = new Cat();
    animals[2] = new Dog();
    animals[3] = new Cat();

    std::cout << "\nAll animals making their specific sounds:" << std::endl;
    for (int i = 0; i < 4; i++)
    {
        std::cout << "Animal[" << i << "] (" << animals[i]->getType() << "): ";
        animals[i]->makeSound();
    }

    std::cout << "\nDeleting array:" << std::endl;
    for (int i = 0; i < 4; i++)
    {
        delete animals[i];
    }

    printSeparator("END OF TESTS");

    return 0;
}
