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

Vector* MakeVector(double x, double y)
{
	//return new Vector(x, y);
	Vector* p;
	if (x > 6)
		p = new Vector(x , y);
	return p;
}

void PrintVector(const Vector& v)
{
	std::cout << "vector: " << v.x << ", " << v.y << std::endl;
	//throw std::runtime_error("Error!!!");
}

void PrintSharedVector(std::shared_ptr<Vector> v)
{
	std::cout << "vector: " << v->x << ", " << v->y << std::endl;
}

void DoSomething(double x)
{
	std::shared_ptr<Vector> p;
	std::weak_ptr<Vector> wp = p;
	
	if (x > 88)
	{
		auto p2 = std::make_shared<Vector>(5, 6);
		p = p2;
	}

	if (p)
	{
		PrintSharedVector(p);
	}
}

int main(int argc, char** argv)
{
	std::cout << "Hello, world!" << std::endl;
	
	double x = 0;
	if (argc > 1)
		x = std::stod(argv[1]);
	
	try
	{
		DoSomething(x);
	}
	catch(const std::exception& e)
	{
		std::cout << "Error: " << e.what() << std::endl;
	}
}

