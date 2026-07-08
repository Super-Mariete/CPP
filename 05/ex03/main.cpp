#include "Bureaucrat.hpp"
#include "Intern.hpp"
#include <fstream>

int main()
{
	Intern intern;
	Bureaucrat boss("Boss", 1);
	AForm* f;

	std::cout << "--- shrubbery creation ---" << std::endl;
	f = intern.makeForm("shrubbery creation", "garden");
	if (f) {
		boss.signForm(*f);
		boss.executeForm(*f);

		// Mostramos el arbol ASCII recien creado
		std::ifstream tree("garden_shrubbery");
		if (tree.is_open())
			std::cout << tree.rdbuf();

		delete f;
	}

	std::cout << "\n--- robotomy request ---" << std::endl;
	f = intern.makeForm("robotomy request", "Bender");
	if (f) {
		boss.signForm(*f);
		boss.executeForm(*f);
		delete f;
	}

	std::cout << "\n--- presidential pardon ---" << std::endl;
	f = intern.makeForm("presidential pardon", "Alice");
	if (f) {
		boss.signForm(*f);
		boss.executeForm(*f);
		delete f;
	}

	std::cout << "\n--- formulario desconocido ---" << std::endl;
	f = intern.makeForm("coffee request", "Bob");
	if (f)
		delete f;

	return 0;
}
