#include <iostream>
#include "Point.hpp"

int main(void)
{
	// Define a triangle with vertices at (0,0), (10,0), and (5,10)
	Point a(0.0f, 0.0f);
	Point b(10.0f, 0.0f);
	Point c(5.0f, 10.0f);

	// Test points
	Point inside(5.0f, 5.0f);		// Inside the triangle
	Point outside(15.0f, 5.0f);		// Outside the triangle
	Point onVertex(0.0f, 0.0f);		// On vertex a
	Point onEdge(5.0f, 0.0f);		// On edge between a and b

	std::cout << "Triangle vertices: A(0,0), B(10,0), C(5,10)" << std::endl;
	std::cout << std::endl;

	// Test point inside
	std::cout << "Point (5, 5): ";
	if (bsp(a, b, c, inside))
		std::cout << "Inside the triangle" << std::endl;
	else
		std::cout << "Outside the triangle" << std::endl;

	// Test point outside
	std::cout << "Point (15, 5): ";
	if (bsp(a, b, c, outside))
		std::cout << "Inside the triangle" << std::endl;
	else
		std::cout << "Outside the triangle" << std::endl;

	// Test point on vertex
	std::cout << "Point (0, 0) [vertex]: ";
	if (bsp(a, b, c, onVertex))
		std::cout << "Inside the triangle" << std::endl;
	else
		std::cout << "Outside the triangle" << std::endl;

	// Test point on edge
	std::cout << "Point (5, 0) [edge]: ";
	if (bsp(a, b, c, onEdge))
		std::cout << "Inside the triangle" << std::endl;
	else
		std::cout << "Outside the triangle" << std::endl;

	return 0;
}
