#pragma once

#include <cmath>
#include <ostream>
#include <stdexcept>

class Vector2d
{
	double mX;
	double mY;

	Vector2d(double x, double y) : mX(x), mY(y) {}

public:
	double GetX() const { return mX;}
	void SetX(double value) { mX = value; }

	double GetY() const { return mY;}
	void SetY(double value) { mY = value; }
	
	double GetRadius() const { return std::sqrt(mX*mX + mY*mY); }
	double GetAngle() const
	{
		return std::atan2(mY, mX);
	}

	static Vector2d FromPolarCoordinates(double radius, double angle)
	{
		if (radius < 0)
			throw std::runtime_error("'radius' cannot be negative");

		return Vector2d(
			radius * std::cos(angle),
			radius * std::sin(angle));
	}

	static Vector2d FromCartesianCoordinates(double x, double y)
	{
		return Vector2d(x,y);
	}

	Vector2d operator+(const Vector2d& other)
	{
		return {mX + other.mX, mY + other.mY};
	}

	bool operator==(const Vector2d& other)
	{
		static const double tolerance = 10e-7;
		return (std::abs(mX - other.mX) < tolerance)
			&& (std::abs(mY - other.mY) < tolerance);
	}
};

std::ostream& operator<<(std::ostream& os, const Vector2d& obj)
{
	os << "("<< obj.GetX() << ", " << obj.GetY() << ")";
	return os;
}