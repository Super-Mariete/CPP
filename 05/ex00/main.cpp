#include "Bureaucrat.hpp"

int main()
{
	// Test valid bureaucrat
	try {
		Bureaucrat alice("Alice", 2);
		std::cout << alice << std::endl;

		alice.incrementGrade();
		std::cout << alice << std::endl;

		alice.incrementGrade(); // should throw
	}
	catch (const std::exception& e) {
		std::cerr << "Exception: " << e.what() << std::endl;
	}

	// Test too high grade at construction
	try {
		Bureaucrat bad("Bad", 0);
	}
	catch (const std::exception& e) {
		std::cerr << "Exception: " << e.what() << std::endl;
	}

	// Test too low grade at construction
	try {
		Bureaucrat bad("Bad", 151);
	}
	catch (const std::exception& e) {
		std::cerr << "Exception: " << e.what() << std::endl;
	}

	// Test decrement at lowest
	try {
		Bureaucrat bob("Bob", 149);
		bob.decrementGrade();
		std::cout << bob << std::endl;
		bob.decrementGrade(); // should throw
	}
	catch (const std::exception& e) {
		std::cerr << "Exception: " << e.what() << std::endl;
	}

	return 0;
}
