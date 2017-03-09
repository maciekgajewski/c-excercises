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
}

std::unique_ptr<Vector> MakeVector(double x, double y)
{
	return std::make_unique<Vector>(x, y);
}

int main(int /*argc*/, char** /*argv*/)
{
	std::cout << "Hello, world!" << std::endl;

	std::unique_ptr<Vector> p = std::make_unique<Vector>();
	std::cout << "vector: " << p->x << ", " << p->y << std::endl;
	
	Vector v2 = *p;
	
	p = std::make_unique<Vector3D>(6, 6, 7);
	std::cout << "vector: " << p->x << ", " << p->y << std::endl;
	
	p = MakeVector(7, 8);
	std::cout << "vector: " << p->x << ", " << p->y << std::endl;
	
	Vector* raw = p.get();
	
	std::unique_ptr<Vector> p2 = std::move(p);
	
	if(p2)
	{
		std::cout << "vector2: " << p2->x << ", " << p2->y << std::endl;
	}
}

