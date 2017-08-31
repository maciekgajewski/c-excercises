#include <iostream>
#include <cstdint>

class Vector
{
public:
	using coord = double;

	coord x = 0.0;
	coord y = 3.14;

	void print();

	Vector() { std::cout << "Vector this=" << this << std::endl; }
	~Vector() { std::cout << "~Vector this=" << this << std::endl; }
};

struct Rectangle
{
	Rectangle() { std::cout << "Rectangle this=" << this << std::endl; }
	~Rectangle() { std::cout << "~Rectangle this=" << this << std::endl; }

	Vector topLeft;
	Vector bottomRight;
};

int main(int argc, char** argv)
{
	Rectangle* p = nullptr;
	{
		Rectangle r;
		p = &r;
	}
	p->topLeft.print();
}

void Vector::print(/* Vector* this */)
{
	std::cout << "Vector(" << x << ", " << y << ")" << std::endl;
}

