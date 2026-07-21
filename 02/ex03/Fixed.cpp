#include "Fixed.hpp"
#include <cmath>

// Default constructor
Fixed::Fixed() : value(0)
{
}

// Copy constructor
Fixed::Fixed(const Fixed& other)
{
	this->value = other.value;
}

// Copy assignment operator
Fixed& Fixed::operator=(const Fixed& other)
{
	if (this != &other)
		this->value = other.getRawBits();
	return *this;
}

// Destructor
Fixed::~Fixed()
{
}

// Int constructor - converts int to fixed-point
Fixed::Fixed(const int n)
{
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

// Comparison operators
bool Fixed::operator>(const Fixed& other) const
{
	return this->value > other.value;
}

bool Fixed::operator<(const Fixed& other) const
{
	return this->value < other.value;
}

bool Fixed::operator>=(const Fixed& other) const
{
	return this->value >= other.value;
}

bool Fixed::operator<=(const Fixed& other) const
{
	return this->value <= other.value;
}

bool Fixed::operator==(const Fixed& other) const
{
	return this->value == other.value;
}

bool Fixed::operator!=(const Fixed& other) const
{
	return this->value != other.value;
}

// Arithmetic operators
Fixed Fixed::operator+(const Fixed& other) const
{
	Fixed result;
	result.setRawBits(this->value + other.value);
	return result;
}

Fixed Fixed::operator-(const Fixed& other) const
{
	Fixed result;
	result.setRawBits(this->value - other.value);
	return result;
}

Fixed Fixed::operator*(const Fixed& other) const
{
	Fixed result;
	result.setRawBits((this->value * other.value) >> fractionalBits);
	return result;
}

Fixed Fixed::operator/(const Fixed& other) const
{
	Fixed result;
	result.setRawBits((this->value << fractionalBits) / other.value);
	return result;
}

// Pre-increment: ++a
Fixed& Fixed::operator++(void)
{
	this->value++;
	return *this;
}

// Post-increment: a++
Fixed Fixed::operator++(int)
{
	Fixed temp(*this);
	this->value++;
	return temp;
}

// Pre-decrement: --a
Fixed& Fixed::operator--(void)
{
	this->value--;
	return *this;
}

// Post-decrement: a--
Fixed Fixed::operator--(int)
{
	Fixed temp(*this);
	this->value--;
	return temp;
}

// Static min function (non-const)
Fixed& Fixed::min(Fixed& a, Fixed& b)
{
	return (a < b) ? a : b;
}

// Static min function (const)
const Fixed& Fixed::min(const Fixed& a, const Fixed& b)
{
	return (a < b) ? a : b;
}

// Static max function (non-const)
Fixed& Fixed::max(Fixed& a, Fixed& b)
{
	return (a > b) ? a : b;
}

// Static max function (const)
const Fixed& Fixed::max(const Fixed& a, const Fixed& b)
{
	return (a > b) ? a : b;
}

// Overload of insertion operator
std::ostream& operator<<(std::ostream& out, const Fixed& fixed)
{
	out << fixed.toFloat();
	return out;
}
