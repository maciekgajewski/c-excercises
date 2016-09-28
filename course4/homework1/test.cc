#include "vector2d.h"

#include <sstream>
#include <cassert>
#include <iostream>

bool AreEqual(Vector2d x, Vector2d y) { return x == y; }

int main()
{
	std::cout << "Starting test..." << std::endl;	

	Vector2d a = Vector2d::FromCartesianCoordinates(5, 6);
	Vector2d b = Vector2d::FromCartesianCoordinates(-1, 7);

	assert(a+b == Vector2d::FromCartesianCoordinates(4, 13));

	std::stringstream s;
	s << a;

	assert(s.str() == "(5, 6)");

	assert(AreEqual(
		Vector2d::FromPolarCoordinates(1, 0),
		Vector2d::FromCartesianCoordinates(1, 0)));
	assert(AreEqual(
		Vector2d::FromPolarCoordinates(1, M_PI),
		Vector2d::FromCartesianCoordinates(-1, 0)));
	assert(AreEqual(
		Vector2d::FromPolarCoordinates(1, M_PI / 2),
		Vector2d::FromCartesianCoordinates(0, 1)));
	assert(AreEqual(
		Vector2d::FromPolarCoordinates(1, -M_PI / 2),
		Vector2d::FromCartesianCoordinates(0, -1)));

	std::cout << "done" << std::endl;
}