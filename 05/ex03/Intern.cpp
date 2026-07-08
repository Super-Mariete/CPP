#include "Intern.hpp"
#include "ShrubberyCreationForm.hpp"
#include "RobotomyRequestForm.hpp"
#include "PresidentialPardonForm.hpp"

Intern::Intern() {}
Intern::Intern(const Intern&) {}
Intern& Intern::operator=(const Intern&) { return *this; }
Intern::~Intern() {}

// Funciones de fabrica: una por cada tipo de formulario
static AForm* makeShrubbery(const std::string& target)
{
	return new ShrubberyCreationForm(target);
}

static AForm* makeRobotomy(const std::string& target)
{
	return new RobotomyRequestForm(target);
}

static AForm* makePardon(const std::string& target)
{
	return new PresidentialPardonForm(target);
}

AForm* Intern::makeForm(const std::string& formName, const std::string& target) const
{
	// Tabla nombre -> funcion de fabrica. Evita cadena if/else.
	struct FormEntry {
		const char*	name;
		AForm*		(*create)(const std::string&);
	};

	static const FormEntry forms[] = {
		{ "shrubbery creation",  makeShrubbery },
		{ "robotomy request",    makeRobotomy  },
		{ "presidential pardon", makePardon    }
	};

	static const int count = 3;

	for (int i = 0; i < count; ++i)
	{
		if (formName == forms[i].name)
		{
			std::cout << "Intern creates " << formName << std::endl;
			return forms[i].create(target);
		}
	}

	std::cerr << "Intern: unknown form \"" << formName << "\"" << std::endl;
	return NULL;
}
