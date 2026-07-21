#ifndef PHONEBOOK_HPP
# define PHONEBOOK_HPP

# include "Contact.hpp"

class PhoneBook
{
private:
	Contact	contacts[8];		// Array de 8 contactos (NO dinámico)
	int		contactCount;		// Número de contactos actuales
	int		oldestIndex;		// Índice del contacto más antiguo

	// Funciones privadas auxiliares
	void	printTableHeader() const;
	bool	isValidIndex(int index) const;

public:
	// Constructor
	PhoneBook();
	
	// Destructor
	~PhoneBook();
	
	// Métodos públicos
	void	addContact(const Contact& contact);
	void	displayContacts() const;
	void	displayContactDetails(int index) const;
	int		getContactCount() const;
};

#endif
