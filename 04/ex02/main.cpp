/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvigara- <mvigara-@student.42school.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/24 14:30:00 by mvigara-          #+#    #+#             */
/*   Updated: 2025/11/24 14:30:00 by mvigara-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Animal.hpp"
#include "Dog.hpp"
#include "Cat.hpp"
#include "Brain.hpp"

void printSeparator(const std::string& title)
{
    std::cout << "\n========== " << title << " ==========\n" << std::endl;
}

int main()
{
    printSeparator("TEST 1: Subject Test - Memory Leak Check");
    {
        const Animal* j = new Dog();
        const Animal* i = new Cat();

        delete j; //should not create a leak
        delete i;
    }

    printSeparator("TEST 2: Array of Animals (Half Dogs, Half Cats)");
    {
        const int size = 6;
        Animal* animals[size];

        std::cout << "Creating animals:" << std::endl;
        for (int idx = 0; idx < size; idx++)
        {
            if (idx < size / 2)
                animals[idx] = new Dog();
            else
                animals[idx] = new Cat();
        }

        std::cout << "\nAll animals making sounds:" << std::endl;
        for (int idx = 0; idx < size; idx++)
        {
            std::cout << animals[idx]->getType() << ": ";
            animals[idx]->makeSound();
        }

        std::cout << "\nDeleting all animals:" << std::endl;
        for (int idx = 0; idx < size; idx++)
        {
            delete animals[idx];
        }
    }

    printSeparator("TEST 3: Deep Copy Test - Dog");
    {
        std::cout << "Creating original dog:" << std::endl;
        Dog originalDog;
        originalDog.getBrain()->setIdea(0, "I want to chase cats!");
        originalDog.getBrain()->setIdea(1, "I love treats!");

        std::cout << "\nCopying dog (copy constructor):" << std::endl;
        Dog copiedDog(originalDog);

        std::cout << "\nChanging original dog's idea:" << std::endl;
        originalDog.getBrain()->setIdea(0, "Actually, I want to sleep!");

        std::cout << "\nOriginal dog's idea[0]: " << originalDog.getBrain()->getIdea(0) << std::endl;
        std::cout << "Copied dog's idea[0]: " << copiedDog.getBrain()->getIdea(0) << std::endl;
        std::cout << "Copied dog's idea[1]: " << copiedDog.getBrain()->getIdea(1) << std::endl;

        if (originalDog.getBrain() != copiedDog.getBrain())
            std::cout << "\n✓ Deep copy successful! Brain addresses are different." << std::endl;
        else
            std::cout << "\n✗ Shallow copy! Brain addresses are the same!" << std::endl;

        std::cout << "\nDestruction:" << std::endl;
    }

    printSeparator("TEST 4: Deep Copy Test - Cat with Assignment");
    {
        std::cout << "Creating original cat:" << std::endl;
        Cat originalCat;
        originalCat.getBrain()->setIdea(0, "I hate dogs!");
        originalCat.getBrain()->setIdea(1, "I love fish!");

        std::cout << "\nCreating another cat and assigning:" << std::endl;
        Cat assignedCat;
        assignedCat.getBrain()->setIdea(0, "Temp idea");
        assignedCat = originalCat;

        std::cout << "\nChanging original cat's idea:" << std::endl;
        originalCat.getBrain()->setIdea(0, "Actually, I'm indifferent to dogs!");

        std::cout << "\nOriginal cat's idea[0]: " << originalCat.getBrain()->getIdea(0) << std::endl;
        std::cout << "Assigned cat's idea[0]: " << assignedCat.getBrain()->getIdea(0) << std::endl;
        std::cout << "Assigned cat's idea[1]: " << assignedCat.getBrain()->getIdea(1) << std::endl;

        if (originalCat.getBrain() != assignedCat.getBrain())
            std::cout << "\n✓ Deep copy successful! Brain addresses are different." << std::endl;
        else
            std::cout << "\n✗ Shallow copy! Brain addresses are the same!" << std::endl;

        std::cout << "\nDestruction:" << std::endl;
    }

    printSeparator("TEST 5: Brain Ideas Storage");
    {
        Dog smartDog;

        std::cout << "Setting multiple ideas:" << std::endl;
        smartDog.getBrain()->setIdea(0, "Fetch the ball");
        smartDog.getBrain()->setIdea(1, "Guard the house");
        smartDog.getBrain()->setIdea(2, "Play with owner");
        smartDog.getBrain()->setIdea(99, "Last idea!");

        std::cout << "\nRetrieving ideas:" << std::endl;
        std::cout << "Idea 0: " << smartDog.getBrain()->getIdea(0) << std::endl;
        std::cout << "Idea 1: " << smartDog.getBrain()->getIdea(1) << std::endl;
        std::cout << "Idea 2: " << smartDog.getBrain()->getIdea(2) << std::endl;
        std::cout << "Idea 99: " << smartDog.getBrain()->getIdea(99) << std::endl;
    }

    printSeparator("END OF TESTS");

    return 0;
}
