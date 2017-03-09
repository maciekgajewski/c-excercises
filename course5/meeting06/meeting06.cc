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

int main(int /*argc*/, char** /*argv*/)
{
	std::cout << "Hello, world!" << std::endl;

	std::unique_ptr<Vector[]> p = std::make_unique<Vector[]>(3);
	
	for(int i = 0; i < 3 ; i++)
	{
		std::cout << "p["<< i << "] = " << p[i].x << ", " << p[i].y << std::endl;
	}
}

