#pragma once

#include <math.h>
#include <ostream>
#include <stdexcept>

const double AngleToRadian = M_PI / 180;

class Vector2d
{
	double mX;
	double mY;

public:
	Vector2d(double x, double y) : mX(x), mY(y) {}

	double GetX() const { return mX;}
	void SetX(double value) { mX = value; }

	double GetY() const { return mY;}
	void SetY(double value) { mY = value; }
	
	double GetRadius() const { return sqrt(mX*mX + mY*mY); }
	double GetAngle() const
	{
		if (mX == 0)
		{
			if (mY == 0)
				return 0; // not really defined

			if (mY > 0)
				return 90;

			return 270;
		}

		if (mX < 0)
			return atan(mY / mX) / AngleToRadian + 180;

		if (mY < 0)
			return atan(mY / mX) / AngleToRadian + 360;

		return atan(mY / mX) / AngleToRadian;
	}

	static Vector2d FromPolarCoordinates(double radius, double angle)
	{
		if (radius < 0)
			throw std::runtime_error("'radius' cannot be negative");

		return Vector2d(
			radius * cos(angle * AngleToRadian),
			radius * sin(angle * AngleToRadian));
	}
};

Vector2d operator+(const Vector2d& a, const Vector2d& b)
{
	return {a.GetX() + b.GetX(), a.GetY() + b.GetY()};
}

bool operator==(const Vector2d& a, const Vector2d& b)
{
	return (a.GetX() == b.GetX()) && (a.GetY() == b.GetY());
}

std::ostream& operator<<(std::ostream& os, const Vector2d& obj)
{
	os << "("<< obj.GetX() << ", " << obj.GetY() << ")";
	return os;
}
