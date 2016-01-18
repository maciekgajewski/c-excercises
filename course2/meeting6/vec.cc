#include <iostream>

template<typename T>
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

	T x;
	T y;
};

template<typename T>
std::ostream& operator<<(std::ostream& o, const Vec<T>& vec)
{
	return o << "(" << vec.x << ", " << vec.y << ")";
}

int main()
{
	Vec<int> v = Vec<int>{1,1} + Vec<int>{4,5};

	std::cout << "v=" << v  << std::endl;
}
