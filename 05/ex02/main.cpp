#include "Bureaucrat.hpp"
#include "ShrubberyCreationForm.hpp"
#include "RobotomyRequestForm.hpp"
#include "PresidentialPardonForm.hpp"
#include <fstream>

int main()
{
	// ShrubberyCreationForm — caso OK: grado suficiente para firmar Y ejecutar
	std::cout << "=== ShrubberyCreationForm (OK: grade 100) ===" << std::endl;
	try {
		Bureaucrat forester("Forester", 100);
		ShrubberyCreationForm shrubbery_ok("forest");
		forester.signForm(shrubbery_ok);
		forester.executeForm(shrubbery_ok);

		// Mostramos el arbol ASCII recien creado
		std::ifstream f("forest_shrubbery");
		if (f.is_open())
			std::cout << f.rdbuf();
	}
	catch (const std::exception& e) {
		std::cerr << "Exception: " << e.what() << std::endl;
	}

	std::cout << std::endl;

	// ShrubberyCreationForm — caso MALO: puede firmar (140<=145) pero no ejecutar (140>137)
	std::cout << "=== ShrubberyCreationForm (FAIL: grade 140 can sign but not execute) ===" << std::endl;
	try {
		Bureaucrat gardener("Gardener", 140);
		ShrubberyCreationForm shrubbery("home");
		gardener.signForm(shrubbery);
		gardener.executeForm(shrubbery);
	}
	catch (const std::exception& e) {
		std::cerr << "Exception: " << e.what() << std::endl;
	}

	std::cout << std::endl;

	// RobotomyRequestForm
	std::cout << "=== RobotomyRequestForm ===" << std::endl;
	try {
		Bureaucrat doctor("Doctor", 45);
		RobotomyRequestForm robotomy("Bender");
		doctor.signForm(robotomy);
		doctor.executeForm(robotomy);
		doctor.executeForm(robotomy);
	}
	catch (const std::exception& e) {
		std::cerr << "Exception: " << e.what() << std::endl;
	}

	std::cout << std::endl;

	// PresidentialPardonForm
	std::cout << "=== PresidentialPardonForm ===" << std::endl;
	try {
		Bureaucrat president("President", 1);
		PresidentialPardonForm pardon("Arthur Dent");
		president.signForm(pardon);
		president.executeForm(pardon);
	}
	catch (const std::exception& e) {
		std::cerr << "Exception: " << e.what() << std::endl;
	}

	std::cout << std::endl;

	// Try to execute without signing
	std::cout << "=== Execute without signing ===" << std::endl;
	try {
		Bureaucrat boss("Boss", 1);
		PresidentialPardonForm unsigned_form("Nobody");
		boss.executeForm(unsigned_form);
	}
	catch (const std::exception& e) {
		std::cerr << "Exception: " << e.what() << std::endl;
	}

	// Try to execute with insufficient grade
	std::cout << std::endl;
	std::cout << "=== Insufficient grade to execute ===" << std::endl;
	try {
		Bureaucrat signer("Signer", 25);
		Bureaucrat lowExec("LowExec", 10);
		PresidentialPardonForm pardon("Target");
		signer.signForm(pardon);
		lowExec.executeForm(pardon);
	}
	catch (const std::exception& e) {
		std::cerr << "Exception: " << e.what() << std::endl;
	}

	return 0;
}
