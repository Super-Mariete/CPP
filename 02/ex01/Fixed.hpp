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
};

// Overload of insertion operator
std::ostream& operator<<(std::ostream& out, const Fixed& fixed);

#endif
