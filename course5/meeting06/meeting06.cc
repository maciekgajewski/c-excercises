#include <iostream>
#include <memory>

class Vector
{
public:
	Vector() = default;
	Vector(double a, double b)
	{
		x = a;
		y = b;
	}

	double x = 0;
	double y = 0;
};

class Vector3D : public Vector
{
public:
	
	Vector3D(double xx, double yy, double zz)
	{
		x = xx;
		y = yy;
		z = zz;
	}
	
	double z = 0;
};

std::unique_ptr<Vector> MakeVector(double x, double y)
{
	return std::make_unique<Vector>(x, y);
}

void PrintVector(const Vector& v)
{
	std::cout << "vector: " << v.x << ", " << v.y << std::endl;
	throw std::runtime_error("Error!!!");
}

void DoSomething()
{
	//Vector* p = new Vector(5, 6); // old C++
	auto p = std::make_unique<Vector>(5, 6);
	PrintVector(*p);
	//delete p;
}

int main(int /*argc*/, char** /*argv*/)
{
	std::cout << "Hello, world!" << std::endl;
	try
	{
		DoSomething();
	}
	catch(const std::exception& e)
	{
		std::cout << "Error: " << e.what() << std::endl;
	}
}

