#include <iostream>
#include <cassert>
#include <iostream>
using namespace std;

class Vector
{
	public:

		Vector()
			: _x{}, _y{}
		{}

		Vector(int initial_x, int initial_y)
			: _x{initial_x}, _y{initial_y}
		{}

		int GetX() const
		{
			return this->_x;
		}

		void SetX(int new_x)
		{
			this->_x = new_x;
		}

		int GetY() const
		{
			return this->_y;
		}

		void SetY(int new_y)
		{
			this->_y = new_y;
		}

		inline bool operator==(const Vector& other) 
		{
			return GetX() == other.GetX() && GetY() == other.GetY();
		}

		inline bool operator!=(const Vector& other)
		{
			return !(*this == other);
		}

		inline Vector operator+(const Vector& other)
		{
			Vector vector(this->GetX() + other.GetX(), this->GetY() + other.GetY());
			return vector;
		}

		friend ostream& operator<<(ostream& os, const Vector& v)
		{
			os << '<' << v.GetX() << ',' << v.GetY() << '>';
			return os;
		}

	private:
		int _x;
		int _y;
};

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
}