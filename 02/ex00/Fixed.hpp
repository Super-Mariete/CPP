#ifndef FIXED_HPP
# define FIXED_HPP

#include <iostream>

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

	// Member functions
	int		getRawBits(void) const;
	void	setRawBits(int const raw);
};

#endif
