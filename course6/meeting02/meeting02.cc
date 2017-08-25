#include <iostream>
#include <cstdint>

int g = 77;

class Vector
{
public:
	int x;
	double y;

	void print();
};

void print(int i) { std::cout << "int: " << i << std::endl; }
void print(double d) { std::cout << "double: " << d << std::endl; }

void print(Vector v) { v.print(); }

int main(int argc, char** argv)
{
	// int a = 7;
	// std::uint64_t b = 88;
	// double c = 3.14;
	// float d = 6.77;
	Vector s;
	
	s.x = 6;
	s.y = 7.7;

	auto p = &s;
	p->x = 88;

	print(s.x);
	print(s.y);
	print(s);
	p->print();
}

void Vector::print(/* Vector* this */)
{
	std::cout << "Vector(" << this->x << ", " << y << ")" << std::endl;
}

