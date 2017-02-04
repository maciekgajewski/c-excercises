#include <iostream>
#include <cassert>

class Vector
{
private:
	int x = 0;
	int y = 0;
public:
	Vector() = default;
	Vector(int _x, int _y) : x(_x), y(_y) { }

	int GetX() const { return x; }
	int GetY() const { return y; }
	void SetX(const int value) { x = value; }
	void SetY(const int value) { y = value; }

	bool operator==(const Vector& other) const
	{
		return x == other.x && y == other.y;
	}

	bool operator!=(const Vector& other) const
	{
		return x != other.x || y != other.y;
	}

	Vector operator+(const Vector& other) const
	{
		return { x + other.x, y + other.y };
	}
};

std::ostream& operator<<(std::ostream& os, const Vector& v)
{
	return os << "(" << v.GetX() << "," << v.GetY() << ")";
}

int main()
{
	// this all should compile and work

	Vector v1;
	Vector v2(5, 6);

	assert(v2.GetX() == 5);
	assert(v2.GetY() == 6);

	v1 = v2;
	assert(v1.GetX() == 5);
	assert(v1.GetY() == 6);
	assert(v1 == v2);

	v1.SetY(7);
	assert(v1.GetY() == 7);
	assert(v1 != v2);

	Vector v3 = v1 + v2;
	assert(v3.GetX() == 10);
	assert(v3.GetY() == 13);

	std::cout << v1 << " + " << v2 << " = " << v3 << std::endl;
	std::cin.get();
}
