#include <iostream>

class Vec
{
public:
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

	std::cout << "v=" << v.x << "," << v.y  << std::endl;
}
