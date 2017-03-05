#include <iostream>
// #include <string>
// #include <cassert>
// #include <cstdio>
// #include <cstring>
// #include <thread>

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
10.   Remember to put your class into a namespace.
***/

class Vector2D
{
public:
	Vector2D(double initX = 0.0, double initY = 0.0) : x(initX), y(initY) {}

	double GetX() const { return x; }
	double GetY() const { return y; }

    void SetX(double newX) { x = newX; }
    void SetY(double newY) { y = newY; }

private:
	double x = 0.0;
	double y = 0.0;
};

std::ostream& operator<<(std::ostream& s, const Vector2D& vec)
{
	s << "(" << vec.GetX() << ", " << vec.GetY() << ")";
	return s;
}

int main(int, char**)
{
    Vector2D defaultVec;
    std::cout << defaultVec << std::endl;

	Vector2D vec(3.14, 3.14);
	std::cout << vec << std::endl;

    vec.SetX(2);
    std::cout << vec << std::endl;

    vec.SetY(4);
    std::cout << vec << std::endl;

    defaultVec = vec;
    std::cout << defaultVec << std::endl;
}
