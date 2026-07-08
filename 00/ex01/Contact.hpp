/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Contact.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: made-ped <made-ped@student.42madrid.c      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/08 21:07:12 by made-ped          #+#    #+#             */
/*   Updated: 2026/07/08 21:07:17 by made-ped         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CONTACT_HPP
# define CONTACT_HPP

# include <string>

class Contact
{
private:
	std::string	firstName;
	std::string	lastName;
	std::string	nickname;
	std::string	phoneNumber;
	std::string	darkestSecret;

	// Función auxiliar privada para formateo
	static std::string	formatField(const std::string& str);

public:
	// Constructor
	Contact();
	
	// Destructor
	~Contact();
	
	// Setter unificado (más eficiente que 5 setters individuales)
	bool	setContact(const std::string& firstName,
					   const std::string& lastName,
					   const std::string& nickname,
					   const std::string& phoneNumber,
					   const std::string& darkestSecret);
	
	// Getters (const & = más eficiente)
	std::string	getFirstName() const;
	std::string	getLastName() const;
	std::string	getNickname() const;
	std::string	getPhoneNumber() const;
	std::string	getDarkestSecret() const;
	
	// Contact se muestra a sí mismo (mejor encapsulación)
	void	displaySummary(int index) const;
	void	displayDetails() const;
	
	// Validación interna
	bool	isEmpty() const;
};

#endif
