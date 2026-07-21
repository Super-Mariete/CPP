#include "Contact.hpp"
#include <iostream>
#include <iomanip>

// Constructor: inicializa con valores vacíos explícitamente
Contact::Contact() : firstName(""), lastName(""), nickname(""),
					 phoneNumber(""), darkestSecret("")
{
}

// Destructor
Contact::~Contact()
{
}

// Función auxiliar privada: formatea campos para la tabla
std::string	Contact::formatField(const std::string& str)
{
	if (str.length() > 10)
		return str.substr(0, 9) + ".";
	// Añade espacios para alinear a la derecha
	return std::string(10 - str.length(), ' ') + str;
}

// SETTER UNIFICADO - Establece todos los campos a la vez
bool	Contact::setContact(const std::string& firstName,
							const std::string& lastName,
							const std::string& nickname,
							const std::string& phoneNumber,
							const std::string& darkestSecret)
{
	// Validación: ningún campo puede estar vacío
	if (firstName.empty() || lastName.empty() || nickname.empty() ||
		phoneNumber.empty() || darkestSecret.empty())
		return false;
	
	// Si todo es válido, guardar
	this->firstName = firstName;
	this->lastName = lastName;
	this->nickname = nickname;
	this->phoneNumber = phoneNumber;
	this->darkestSecret = darkestSecret;
	
	return true;
}

// GETTERS - Devuelven los valores de los campos
std::string	Contact::getFirstName() const
{
	return this->firstName;
}

std::string	Contact::getLastName() const
{
	return this->lastName;
}

std::string	Contact::getNickname() const
{
	return this->nickname;
}

std::string	Contact::getPhoneNumber() const
{
	return this->phoneNumber;
}

std::string	Contact::getDarkestSecret() const
{
	return this->darkestSecret;
}

// DISPLAY SUMMARY - Contact se muestra en formato tabla
void	Contact::displaySummary(int index) const
{
	std::cout << std::setw(10) << index << "|"
			  << formatField(this->firstName) << "|"
			  << formatField(this->lastName) << "|"
			  << formatField(this->nickname) << std::endl;
}

// DISPLAY DETAILS - Contact muestra todos sus detalles
void	Contact::displayDetails() const
{
	std::cout << std::endl;
	std::cout << "First Name: " << this->firstName << std::endl;
	std::cout << "Last Name: " << this->lastName << std::endl;
	std::cout << "Nickname: " << this->nickname << std::endl;
	std::cout << "Phone Number: " << this->phoneNumber << std::endl;
	std::cout << "Darkest Secret: " << this->darkestSecret << std::endl;
}

// IS EMPTY - Verifica si el contacto está vacío
bool	Contact::isEmpty() const
{
	return this->firstName.empty() || this->lastName.empty() ||
		   this->nickname.empty() || this->phoneNumber.empty() ||
		   this->darkestSecret.empty();
}
