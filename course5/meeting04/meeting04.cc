#include <iostream>


class Vector
{
public:
	void Init(int x, int y) // Vector::Init(Vector* this, int xx, int yy)
	{
		this->x = x;
		this->y = y;
	}
	
	int GetX() { return x; }
	int GetY() { return y; }
	
	Vector operator + (Vector rhs)
	{
		Vector v; 
		v.Init(this->x + rhs.x, this->y + rhs.y);
		return v;
	}
	
private:
	int x = 0;
	int y = 0;
};

std::ostream& operator<<(std::ostream& stream, Vector vec)
{
	stream << "(" << vec.GetX() << ", " << vec.GetY() << ")";
	return stream;
}

void print(Vector vec)
{
	std::cout << vec << std::endl;
}

int main(int /*argc*/, char** /*argv*/)
{
	Vector v; // constructor call
	print(v);
	v.Init(55, 77);
	
	Vector x;
	x.Init(6, 8);
	
	print(v + x);
} // destructor 

