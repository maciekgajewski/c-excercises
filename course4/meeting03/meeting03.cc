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
	std::string s1; // default construction
	std::string s2("hey!"); // initilizing constructor
	std::string s3(s2); // copy constructor
	std::string s4 = s2; // copy constructor
	s3 = s4; // copy assignment

	s1 = std::move(s2); // move assignment
	
	std::string s5(std::move(s3)); // move construction
}

