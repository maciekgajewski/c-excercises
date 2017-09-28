#include <iostream>
#include <string>
#include <cstring>

#include "vector.hh"

int main(int argc, char** argv)
{
	Vec2<int> v{1, 4};
	Vec2<double> v2{5.6, 6.6};

	Vec2<std::string> v3{"hey", "you!"};

	v.print();
	v2.print();
	v3.print();

	Vec2<float>{5.5,6.6}.print();
}

