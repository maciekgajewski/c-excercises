#include "vector2d.h"
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

int main(int, char**)
{
    using namespace vector;

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
