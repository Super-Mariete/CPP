#include "Bureaucrat.hpp"
#include "Form.hpp"

int main()
{
	// Bureaucrat with grade too high to sign
	try {
		Bureaucrat lowRank("LowRank", 100);
		Form topSecret("TopSecret", 50, 20);
		std::cout << topSecret << std::endl;
		lowRank.signForm(topSecret);
		std::cout << topSecret << std::endl;
	}
	catch (const std::exception& e) {
		std::cerr << "Exception: " << e.what() << std::endl;
	}

	std::cout << std::endl;

	// Bureaucrat with sufficient grade
	try {
		Bureaucrat highRank("HighRank", 30);
		Form topSecret("TopSecret", 50, 20);
		std::cout << topSecret << std::endl;
		highRank.signForm(topSecret);
		std::cout << topSecret << std::endl;
	}
	catch (const std::exception& e) {
		std::cerr << "Exception: " << e.what() << std::endl;
	}

	std::cout << std::endl;

	// Invalid form grade
	try {
		Form bad("Bad", 0, 10);
	}
	catch (const std::exception& e) {
		std::cerr << "Exception: " << e.what() << std::endl;
	}

	return 0;
}
