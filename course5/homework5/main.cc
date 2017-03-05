#include "vector2d.h"

#include <iostream>
#include <cassert>
#include <cmath>

const double pi = std::acos(-1);

using namespace Vector;

int main()
{
	Vector2D a(1.0, 2.0);
	Vector2D b(4.0, 3.0);

	{
		auto c = a;
		c += b;
		assert(c.GetX() == 5.0 && c.GetY() == 5.0);
	}

	{
		auto c = a + b;
		assert(c.GetX() == 5.0 && c.GetY() == 5.0);
	}

	{
		auto c = b;
		c -= a;
		assert(c.GetX() == 3.0 && c.GetY() == 1.0);
	}

	{
		auto c = b - a;
		assert(c.GetX() == 3.0 && c.GetY() == 1.0);
	}

	{
		assert(a != b);
		assert(Vector2D(1.0, 2.0) == a);
	}

	{
		Vector2D c(0, 10);
		assert(c.GetRad() == 10.0);
		assert(c.GetTheta() == (pi / 2));
	}

	{
		Vector2D c(2, 2);
		assert(c.GetTheta() == (pi / 4));
	}

	{
		Vector2D c(3, 4);
		assert(c.GetRad() == 5.0);
	}

	{
		auto vec = 3.3_x + 0.7_y;
		assert(vec == Vector2D(3.3, 0.7));
	}

	{
		auto vec = 3.3_r + 1.0_t;
		assert(vec.GetRad() == 3.3 && vec.GetTheta() == 1.0);
	}

	{
		auto vec = 1.0_t + 3.3_r;
		assert(vec.GetRad() == 3.3 && vec.GetTheta() == 1.0);
	}
}

