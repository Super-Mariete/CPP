/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Fixed.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvigara- <mvigara-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/17 09:55:17 by mvigara-          #+#    #+#             */
/*   Updated: 2025/11/04 19:43:06 by mvigara-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Fixed.hpp"

// Default constructor
Fixed::Fixed() : value(0)
{
	std::cout << "Default constructor called" << std::endl;
}

// Copy constructor
Fixed::Fixed(const Fixed& other)
{
	std::cout << "Copy constructor called" << std::endl;
	this->value = other.value;
}

// Copy assignment operator
Fixed& Fixed::operator=(const Fixed& other)
{
	std::cout << "Copy assignment operator called" << std::endl;
	if (this != &other)
		this->value = other.getRawBits();
	return *this;
}

// Destructor
Fixed::~Fixed()
{
	std::cout << "Destructor called" << std::endl;
}

// Int constructor - converts int to fixed-point
Fixed::Fixed(const int n)
{
	std::cout << "Int constructor called" << std::endl;
	this->value = n << fractionalBits;
}

// Float constructor - converts float to fixed-point
Fixed::Fixed(const float f)
{
    std::cout << "Float constructor called" << std::endl;
    float scaled = f * (1 << fractionalBits);
    
    if (scaled >= 0)
        this->value = static_cast<int>(scaled + 0.5f);
    else
        this->value = static_cast<int>(scaled - 0.5f);
}

// Converts fixed-point to float
float Fixed::toFloat(void) const
{
	return (float)this->value / (1 << fractionalBits);
}

// Converts fixed-point to int
int Fixed::toInt(void) const
{
	return this->value >> fractionalBits;
}

// Returns the raw value of the fixed-point number
int Fixed::getRawBits(void) const
{
	return this->value;
}

// Sets the raw value of the fixed-point number
void Fixed::setRawBits(int const raw)
{
	this->value = raw;
}

// Overload of insertion operator
std::ostream& operator<<(std::ostream& out, const Fixed& fixed)
{
	out << fixed.toFloat();
	return out;
}
