/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Point.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvigara- <mvigara-@student.42school.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/17 00:00:00 by mvigara-             #+#    #+#             */
/*   Updated: 2025/10/17 00:00:00 by mvigara-            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Point.hpp"

// Default constructor - initializes point to (0, 0)
Point::Point() : x(0), y(0)
{
}

// Constructor with parameters - initializes point to (x, y)
Point::Point(const float x, const float y) : x(x), y(y)
{
}

// Copy constructor
Point::Point(const Point& other) : x(other.x), y(other.y)
{
}

// Copy assignment operator
// Note: Since x and y are const, we cannot actually reassign them
// This operator doesn't do much, but it's required for Orthodox Canonical Form
Point& Point::operator=(const Point& other)
{
	(void)other;
	return *this;
}

// Destructor
Point::~Point()
{
}

// Getters
Fixed Point::getX(void) const
{
	return this->x;
}

Fixed Point::getY(void) const
{
	return this->y;
}
