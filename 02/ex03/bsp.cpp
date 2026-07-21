#include "Point.hpp"

/*
** Calculates the area of a triangle using the cross product formula
** Area = |((x1(y2 - y3) + x2(y3 - y1) + x3(y1 - y2)) / 2)|
*/
static Fixed	calculateArea(Point const p1, Point const p2, Point const p3)
{
	Fixed area;

	area = ((p1.getX() * (p2.getY() - p3.getY())) +
			(p2.getX() * (p3.getY() - p1.getY())) +
			(p3.getX() * (p1.getY() - p2.getY()))) / Fixed(2);

	// Return absolute value
	if (area < Fixed(0))
		area = area * Fixed(-1);

	return area;
}

/*
** BSP (Binary Space Partitioning) function
** Determines if a point is inside a triangle using the area method:
** - If point is inside, sum of areas of 3 sub-triangles equals total area
** - If point is on edge or vertex, returns false
*/
bool bsp(Point const a, Point const b, Point const c, Point const point)
{
	Fixed	totalArea;
	Fixed	area1;
	Fixed	area2;
	Fixed	area3;

	// Calculate total area of triangle ABC
	totalArea = calculateArea(a, b, c);

	// Calculate areas of sub-triangles
	area1 = calculateArea(point, b, c);	// PBC
	area2 = calculateArea(a, point, c);	// APC
	area3 = calculateArea(a, b, point);	// ABP

	// If any area is 0, point is on an edge or vertex
	if (area1 == Fixed(0) || area2 == Fixed(0) || area3 == Fixed(0))
		return false;

	// If sum of sub-areas equals total area, point is inside
	return (area1 + area2 + area3 == totalArea);
}
