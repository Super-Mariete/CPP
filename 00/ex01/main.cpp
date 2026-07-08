/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: made-ped <made-ped@student.42madrid.c      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/08 21:07:40 by made-ped          #+#    #+#             */
/*   Updated: 2026/07/08 21:07:46 by made-ped         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "PhoneBook.hpp"
#include "Contact.hpp"
#include <iostream>
#include <string>
#include <limits>
#include <cstdlib>

// Función auxiliar para pedir input al usuario
static std::string	prompt(const std::string& message)
{
	std::string	input;

	while (true)
	{
		std::cout << message;
		std::getline(std::cin, input);
		
		// Verificar EOF (Ctrl+D)
		if (std::cin.eof())
		{
			std::cout << std::endl << "Goodbye!" << std::endl;
			exit(0);
		}
		
		// Verificar que no esté vacío
		if (!input.empty())
			break;
		
		std::cout << "Field cannot be empty!" << std::endl;
	}
	return input;
}

// Función para manejar el comando ADD
static void	handleAdd(PhoneBook& phoneBook)
{
	Contact		contact;
	std::string	firstName;
	std::string	lastName;
	std::string	nickname;
	std::string	phoneNumber;
	std::string	darkestSecret;

	// Pedir todos los campos
	firstName = prompt("First Name: ");
	lastName = prompt("Last Name: ");
	nickname = prompt("Nickname: ");
	phoneNumber = prompt("Phone Number: ");
	darkestSecret = prompt("Darkest Secret: ");

	// Crear el contacto con validación
	if (!contact.setContact(firstName, lastName, nickname, phoneNumber, darkestSecret))
	{
		std::cout << "Error: All fields must be filled!" << std::endl;
		return;
	}

	// Añadir a la agenda
	phoneBook.addContact(contact);
	std::cout << "Contact added successfully!" << std::endl;
}

// Función para manejar el comando SEARCH
static void	handleSearch(const PhoneBook& phoneBook)
{
	std::string	input;
	int			index;

	// Verificar si hay contactos
	if (phoneBook.getContactCount() == 0)
	{
		std::cout << "PhoneBook is empty!" << std::endl;
		return;
	}

	// Mostrar la tabla de contactos
	phoneBook.displayContacts();

	// Pedir el índice
	std::cout << "Enter index: ";
	std::getline(std::cin, input);

	// Verificar EOF
	if (std::cin.eof())
	{
		std::cout << std::endl << "Goodbye!" << std::endl;
		exit(0);
	}

	// Convertir y validar el índice
	if (input.length() == 1 && input[0] >= '0' && input[0] <= '7')
	{
		index = input[0] - '0';
		phoneBook.displayContactDetails(index);
	}
	else
	{
		std::cout << "Invalid index! Please enter a number between 0 and 7." << std::endl;
	}
}

int	main(void)
{
	PhoneBook	phoneBook;
	std::string	command;

	std::cout << "╔════════════════════════════════════╗" << std::endl;
	std::cout << "║  Welcome to My Awesome PhoneBook! ║" << std::endl;
	std::cout << "╚════════════════════════════════════╝" << std::endl;
	std::cout << "Commands: ADD, SEARCH, EXIT" << std::endl;

	while (true)
	{
		std::cout << std::endl << "> ";
		std::getline(std::cin, command);

		// Verificar EOF (Ctrl+D)
		if (std::cin.eof())
		{
			std::cout << std::endl << "Goodbye!" << std::endl;
			break;
		}

		// Procesar comandos
		if (command == "ADD")
			handleAdd(phoneBook);
		else if (command == "SEARCH")
			handleSearch(phoneBook);
		else if (command == "EXIT")
		{
			std::cout << "Goodbye!" << std::endl;
			break;
		}
		else if (!command.empty())
			std::cout << "Invalid command! Use: ADD, SEARCH, or EXIT" << std::endl;
	}

	return 0;
}
