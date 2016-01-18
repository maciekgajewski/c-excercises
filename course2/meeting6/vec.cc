#include <iostream>

class Vec
{
public:
	//Vec(double x, double y) : mX(x), mY(y) {}
	//Vec() = default;

	//double GetX() const { return mX; }
	//double GetY() const { return mY; }

	bool operator == (const Vec& o) const
	{
		return x == o.x && y == o.y;
	}

	Vec operator + (const Vec& o) const
	{
		return Vec{x + o.x, y + o.y};
	}

	double x;
	double y;
};

int main()
{
	Vec v = Vec{1,1} + Vec{4,5};

	std::cout << "v=" << v.x << ", " << v.y << std::endl;
}
