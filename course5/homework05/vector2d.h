#ifndef vector2d_h
#define vector2d_h

#include <string>
#include <cstdio>
#include <iostream>
#include <cmath>

// ARS -- week 05. 20170301

namespace vector2D
{

class Vector2D;

class Vector2D
{
private:
	double mX;
	double mY;
public:
	Vector2D();
	Vector2D(double x, double y);
	~Vector2D();
	double GetX() const;
	double GetY() const;
	void SetX(double x);
	void SetY(double y);
	double GetPolarR();
	double GetPolarPhi();
	Vector2D& operator+ ();  // unary, idempotent funtion
	Vector2D operator+ (const Vector2D& rhs);
	Vector2D operator- (); // unary
	Vector2D operator- (const Vector2D& rhs);
	Vector2D& operator+=(const Vector2D& rhs);
	Vector2D& operator-=(const Vector2D& rhs);
	bool operator==(const Vector2D& rhs);
	bool operator!=(const Vector2D& rhs);

	Vector2D operator*(const double r); // for polar init: multiply the (cos phi, sin phi) vector with the radius r

};

inline std::ostream& operator<<(std::ostream& str, const Vector2D& v)
{
	str << "(" << v.GetX() << ", " << v.GetY() << ") " ;
	return str;
}


inline Vector2D operator"" _x(long double first)
{ 
	return Vector2D(first, 0.0);
}

inline Vector2D operator"" _y(long double y)
{ 
	return Vector2D(0.0, y);
}

inline Vector2D operator"" _tocart(long double phi)
{ 
	return Vector2D(cos(phi),sin(phi));
}

}; // namespace

#endif
