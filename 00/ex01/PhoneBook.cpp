/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PhoneBook.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: made-ped <made-ped@student.42madrid.c      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/08 21:08:11 by made-ped          #+#    #+#             */
/*   Updated: 2026/07/08 21:08:17 by made-ped         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "PhoneBook.hpp"
#include <iostream>
#include <iomanip>

// Constructor: lista de inicialización (más eficiente)
PhoneBook::PhoneBook() : contactCount(0), oldestIndex(0)
{
}

// Destructor
PhoneBook::~PhoneBook()
{
}

// Imprime el encabezado de la tabla
void	PhoneBook::printTableHeader() const
{
	std::cout << std::setw(10) << "Index" << "|"
			  << std::setw(10) << "First Name" << "|"
			  << std::setw(10) << "Last Name" << "|"
			  << std::setw(10) << "Nickname" << std::endl;
}

// Verifica si un índice es válido
bool	PhoneBook::isValidIndex(int index) const
{
	return (index >= 0 && index < this->contactCount);
}

// ADD CONTACT - Añade un contacto a la agenda
void	PhoneBook::addContact(const Contact& contact)
{
	int	index;

	// Determinar el índice donde guardar
	if (this->contactCount < 8)
	{
		index = this->contactCount;
		this->contactCount++;
	}
	else
	{
		// Si ya hay 8, reemplazar el más antiguo
		index = this->oldestIndex;
		this->oldestIndex = (this->oldestIndex + 1) % 8;
	}

	// Guardar el contacto
	this->contacts[index] = contact;
}

// DISPLAY CONTACTS - Muestra todos los contactos en formato tabla
void	PhoneBook::displayContacts() const
{
	if (this->contactCount == 0)
	{
		std::cout << "PhoneBook is empty!" << std::endl;
		return;
	}

	this->printTableHeader();
	for (int i = 0; i < this->contactCount; i++)
		this->contacts[i].displaySummary(i);  // Contact se muestra a sí mismo
}

// DISPLAY CONTACT DETAILS - Muestra los detalles de un contacto
void	PhoneBook::displayContactDetails(int index) const
{
	if (!this->isValidIndex(index))
		std::cout << "Invalid index!" << std::endl;
	else
		this->contacts[index].displayDetails();  // Contact se muestra a sí mismo
}

// GET CONTACT COUNT - Devuelve el número de contactos
int		PhoneBook::getContactCount() const
{
	return this->contactCount;
}
