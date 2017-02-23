#include <iostream>


class Vector
{
public:
	
	// Constructors
	Vector() // default contructor
	{
		std::cout << "Vector::Vector()" << std::endl;
	}
	
	Vector(const Vector& src) // copy
	{
		std::cout << "Vector::Vector(const Vector&)" << std::endl;
		x = src.x;
		y = src.y;
	}
	Vector(Vector&& src) // move
	{
		std::cout << "Vector::Vector(Vector&&)" << std::endl;
		x = src.x;
		y = src.y;
	}
	// user-defined constructors
	Vector(int x, int y)
	{
		std::cout << "Vector::Vector(int, int)" << std::endl;
		this->x = x;
		this->y = y;
	}
	
	// Destructor
	~Vector()
	{
		std::cout << "Vector::~Vector()" << std::endl;
	}
	
	// assignment operators
	Vector& operator=(const Vector& src)
	{
		std::cout << "Vector::operator=(const Vector&)" << std::endl;
		x = src.x;
		y = src.y;
		return *this;
	}
	
	Vector& operator=(Vector&& src)
	{
		std::cout << "Vector::operator=(Vector&&)" << std::endl;
		x = src.x;
		y = src.y;
		return *this;
	}

	void Init(int x, int y) // Vector::Init(Vector* this, int xx, int yy)
	{
		this->x = x;
		this->y = y;
	}
	
	int GetX() { return x; }
	int GetY() { return y; }
	
	Vector operator + (Vector rhs)
	{
		Vector v(this->x + rhs.x, this->y + rhs.y); 
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
	Vector v = {55, 77}; // constructor call
	print(v);
	std::cout << "Checkpoint #1" << std::endl;
	
	Vector x(6, 8);
	v = x;
	v = v+x;
	
	print(v + x);
} // destructor 

