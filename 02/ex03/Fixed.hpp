/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Fixed.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvigara- <mvigara-@student.42school.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/25 10:01:55 by mvigara-          #+#    #+#             */
/*   Updated: 2025/10/25 10:01:57 by mvigara-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FIXED_HPP
# define FIXED_HPP

# include <iostream>

class Fixed
{
private:
	int					value;
	static const int	fractionalBits = 8;

public:
	// Orthodox Canonical Form
	Fixed();								// Default constructor
	Fixed(const Fixed& other);				// Copy constructor
	Fixed& operator=(const Fixed& other);	// Copy assignment operator
	~Fixed();								// Destructor

	// Additional constructors
	Fixed(const int n);						// Int constructor
	Fixed(const float f);					// Float constructor

	// Conversion functions
	float	toFloat(void) const;
	int		toInt(void) const;

	// Member functions
	int		getRawBits(void) const;
	void	setRawBits(int const raw);

	// Comparison operators
	bool	operator>(const Fixed& other) const;
	bool	operator<(const Fixed& other) const;
	bool	operator>=(const Fixed& other) const;
	bool	operator<=(const Fixed& other) const;
	bool	operator==(const Fixed& other) const;
	bool	operator!=(const Fixed& other) const;

	// Arithmetic operators
	Fixed	operator+(const Fixed& other) const;
	Fixed	operator-(const Fixed& other) const;
	Fixed	operator*(const Fixed& other) const;
	Fixed	operator/(const Fixed& other) const;

	// Increment/Decrement operators
	Fixed&	operator++(void);		// Pre-increment
	Fixed	operator++(int);		// Post-increment
	Fixed&	operator--(void);		// Pre-decrement
	Fixed	operator--(int);		// Post-decrement

	// Static member functions
	static Fixed&		min(Fixed& a, Fixed& b);
	static const Fixed&	min(const Fixed& a, const Fixed& b);
	static Fixed&		max(Fixed& a, Fixed& b);
	static const Fixed&	max(const Fixed& a, const Fixed& b);
};

// Overload of insertion operator
std::ostream& operator<<(std::ostream& out, const Fixed& fixed);

#endif
