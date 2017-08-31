#include <iostream>
#include <cstdint>

class Vector
{
public:
	double x;
	double y;

	void print();
};

int main(int argc, char** argv)
{
	Vector s;
	
	s.x = 6;
	s.y = 7.7;

	s.print();
}

void Vector::print(/* Vector* this */)
{
	std::cout << "Vector(" << this->x << ", " << y << ")" << std::endl;
}

