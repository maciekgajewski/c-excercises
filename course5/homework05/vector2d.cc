#include "vector2d.h"
#include <cmath> 

using namespace vector2D;

Vector2D::Vector2D()
{
	mX = 0.0;
	mY = 0.0;
}


Vector2D::Vector2D(double x, double y)
{
	mX = x;
	mY = y;
}

Vector2D::~Vector2D()
{
	// empty. Could maybe use the delete option
}

double Vector2D::GetX() const 
{
	return mX;
}

double Vector2D::GetY() const 
{
	return mY;
}

void Vector2D::SetX(double x)
{
	mX = x;
}

void Vector2D::SetY(double y)
{
	mY = y;
}

// from https://en.m.wikipedia.org/wiki/Polar_coordinate_system 
double Vector2D::GetPolarR()
{
	return sqrt(mX*mX + mY*mY);
}

double Vector2D::GetPolarPhi()
{
	return atan2(mY, mX);
}

Vector2D Vector2D::operator*(const double r)
{
	Vector2D v(mX*r, mY*r);
	return v;
}

Vector2D& Vector2D::operator+()  // unary, idempotent funtion
{
	return *this;
}

Vector2D Vector2D::operator+ (const Vector2D& rhs)
{
	Vector2D v = Vector2D(mX + rhs.mX, mY + rhs.mY);
	return  v;
}

Vector2D Vector2D::operator-() // unary
{
	Vector2D v(-mX, -mY);
	return v;
}

Vector2D Vector2D::operator- (const Vector2D& rhs)
{
	Vector2D v = Vector2D(mX - rhs.mX, mY - rhs.mY);
	return v;
}

Vector2D& Vector2D::operator+=(const Vector2D& rhs)
{
	mX += rhs.mX;
	mY += rhs.mY;
	return *this;
}

Vector2D& Vector2D::operator-=(const Vector2D& rhs)
{
	mX -= rhs.mX;
	mY -= rhs.mY;
	return *this;
}

bool Vector2D::operator==(const Vector2D& rhs)
{
	return mX == rhs.mX && mY == rhs.mY;
}

bool Vector2D::operator!=(const Vector2D& rhs)
{
	return mX != rhs.mX || mY != rhs.mY;
}
