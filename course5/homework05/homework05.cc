#include <iostream>
#include <cmath>
#include <string>
#include <cassert>

/***
1.       Write a Vector2D class, that has 2 double fields: x, y
2.       Make the fields private, provide getters, setters, initializing constructor
3.       Provide getters for polar coordinates as well.
4.       Overload basic operators: +, - (binary and unary), +=, -=, ==, !=
5.       Overload operator<< for printing with ostream
6.       Implement user-defined literals, so that the vector can be initialized like this: auto vec = 3.3_x + 0.7_y; assert(vec==Vectror2D(3.3, 0.7));
7.       Can you come with similar way of initializing vector with user-defined literals, but from polar coordinates?
8.       Let’s apply some more proper structure to the project: put the class’ definition into vector2d.h, class implementation into vector2d.cc, main function with all the unit tests in main.cc
9.       Make sure you test all the functionality!
10.      Remember to put your class into a namespace.
***/

class Vector2D
{
public:
    enum class System { CARTESIAN, POLAR };

	Vector2D(double initX = 0.0, double initY = 0.0) : x(initX), y(initY) {}

    Vector2D(double arg1, double arg2, System system)
    {
        double initX;
        double initY;
        switch(system)
        {
        case System::POLAR:
            initX = arg1 * std::cos(arg2);
            initY = arg1 * std::sin(arg2);
            break;
        case System::CARTESIAN:
            initX = arg1;
            initY = arg2;
            break;
        }
        x = initX;
        y = initY;
    }

	double GetX() const { return x; }
	double GetY() const { return y; }

    void SetX(double newX) { x = newX; }
    void SetY(double newY) { y = newY; }

    double GetR() const { return std::sqrt(x*x + y*y); }
    double GetTheta() const { return std::atan2(y, x); }

    std::string AsPolar() const
    {
        return "(" + std::to_string(GetR()) + "-r, " + std::to_string(GetTheta()) + "-theta)";
    }

    Vector2D operator+(const Vector2D& vec) const
	{
		return Vector2D(x + vec.x, y + vec.y);
	}

    Vector2D operator-() const
	{
		return Vector2D(-x, -y);
	}

    Vector2D operator-(const Vector2D& vec) const
	{
		return Vector2D(x - vec.x, y - vec.y);
	}

    void operator+=(const Vector2D& vec)
	{
		x = x + vec.x;
		y = y + vec.y;
	}

    void operator-=(const Vector2D& vec)
	{
		x = x - vec.x;
		y = y - vec.y;
	}

    bool operator==(const Vector2D& vec) const
	{
		return (x == vec.x) && (y == vec.y);
	}

    bool operator!=(const Vector2D& vec) const
	{
		return !(*this == vec);
	}

private:
	double x = 0.0;
	double y = 0.0;
};

std::ostream& operator<<(std::ostream& s, const Vector2D& vec)
{
	s << "(" << vec.GetX() << ", " << vec.GetY() << ")";
	return s;
}

Vector2D operator "" _x(long double initX){ return Vector2D(initX, 0.0);}
Vector2D operator "" _y(long double initY){ return Vector2D(0.0, initY);}

Vector2D operator "" _r(long double initR){ return Vector2D(initR, 0.0, Vector2D::System::POLAR);}
Vector2D operator "" _theta(long double initTheta){ return Vector2D(std::cos(0.0), initTheta, Vector2D::System::POLAR);}

int main(int, char**)
{
    Vector2D defaultVec;
    std::cout << defaultVec << std::endl;
    std::cout << defaultVec.AsPolar() << std::endl;

	Vector2D vec(3.14, 3.14);
	std::cout << vec << std::endl;
    std::cout << vec.AsPolar() << std::endl;

    vec.SetX(2);
    std::cout << vec << std::endl;
    std::cout << vec.AsPolar() << std::endl;

    vec.SetY(4);
    std::cout << vec << std::endl;
    std::cout << vec.AsPolar() << std::endl;

    defaultVec = vec;
    std::cout << defaultVec << std::endl;

    Vector2D addedVec = Vector2D(1, 3) + Vector2D(2, 1);
    std::cout << addedVec << std::endl;

    Vector2D subtractedVec = Vector2D(4, 5) - Vector2D(2, 1);
    std::cout << subtractedVec << std::endl;

    Vector2D negatedVec = -Vector2D(1, 2);
    std::cout << negatedVec << std::endl;

    Vector2D otherVec(1, 3);
    std::cout << "Increment assigning vector " << vec << " with " << otherVec << std::endl;
    vec += otherVec;
    std::cout << vec << std::endl;

    std::cout << "And decrement assigning vector " << vec << " with " << otherVec << std::endl;
    vec -= otherVec;
    std::cout << vec << std::endl;

    std::cout << "Equality: " << std::endl;
    bool equals = vec == otherVec;
    std::cout << equals << std::endl;
    equals = vec == vec;
    std::cout << equals << std::endl;
    equals = Vector2D(2, 4) == vec;
    std::cout << equals << std::endl;

    std::cout << "Non-equality: " << std::endl;
    equals = vec != otherVec;
    std::cout << equals << std::endl;
    equals = vec != vec;
    std::cout << equals << std::endl;
    equals = Vector2D(2, 4) != vec;
    std::cout << equals << std::endl;

    auto autovec = 3.3_x + 0.7_y;
    std::cout << autovec << std::endl;
    assert(autovec==Vector2D(3.3, 0.7));

    auto autovecPolar = 4.472136_r;
    auto autovecPolar2 =  1.107149_theta;
    std::cout << autovecPolar.AsPolar() << std::endl;
    std::cout << autovecPolar2.AsPolar() << std::endl;
    std::cout << (autovecPolar + autovecPolar2).AsPolar() << std::endl;
}
