#include <iostream>
#include <string>

class Vector
{
	double x = 0;
	double y = 0;
public:

	Vector(double ax, double ay)
	{
		x = ax;
		y = ay;
	}
	
	void setX(double x)
	{
		this->x = x;
	}
	double getX() const
	{
		return x;
	}
};

void print(const Vector& v)
{
	std::cout << "x=" << v.getX() << std::endl;
}

int main(int argc, char** argv)
{
	Vector v(7, 6);
	
	auto v2 = Vector(6, 88);
	
	
	//v.setX(5);

	print(v);
	print({666, 777});
	//std::cout << v.getX() << std::endl;
	
}

