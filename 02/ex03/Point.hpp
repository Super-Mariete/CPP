/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Point.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvigara- <mvigara-@student.42school.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/17 00:00:00 by mvigara-             #+#    #+#             */
/*   Updated: 2025/10/17 00:00:00 by mvigara-            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef POINT_HPP
# define POINT_HPP

# include "Fixed.hpp"

class Point
{
private:
	Fixed const	x;
	Fixed const	y;

public:
	// Orthodox Canonical Form
	Point();									// Default constructor
	Point(const float x, const float y);		// Constructor with parameters
	Point(const Point& other);					// Copy constructor
	Point& operator=(const Point& other);		// Copy assignment operator
	~Point();									// Destructor

	// Getters
	Fixed	getX(void) const;
	Fixed	getY(void) const;
};

// BSP function - Binary Space Partitioning
bool bsp(Point const a, Point const b, Point const c, Point const point);

#endif
