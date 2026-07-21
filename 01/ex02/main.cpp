#include <string>
#include <iostream>

int main(void)
{
	// Original string variable
	std::string brain = "HI THIS IS BRAIN";

	// Pointer to the string
	std::string* stringPTR = &brain;

	// Reference to the string (alias)
	std::string& stringREF = brain;

	// Print memory addresses
	std::cout << "=== MEMORY ADDRESSES ===" << std::endl;
	std::cout << "Address of brain:       " << &brain << std::endl;
	std::cout << "Address in stringPTR:   " << stringPTR << std::endl;
	std::cout << "Address of stringREF:   " << &stringREF << std::endl;

	// Print values
	std::cout << "\n=== VALUES ===" << std::endl;
	std::cout << "Value of brain:         " << brain << std::endl;
	std::cout << "Value pointed by PTR:   " << *stringPTR << std::endl;
	std::cout << "Value pointed by REF:   " << stringREF << std::endl;

	return 0;
}
