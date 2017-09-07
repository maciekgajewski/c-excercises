#include <iostream>
#include <iomanip>
#include <cmath>

struct Vector
{
private:
	double x;
	double y;

	mutable double cachedLen = 0.0;

public:

	Vector(double xx, double yy) { x = xx; y = yy; }

	void SetX(double xx) { x = xx; cachedLen = 0.0; }
	void SetY(double yy) { y = yy; cachedLen = 0.0; }

	double GetLength() const {
		if (cachedLen == 0.0)
			cachedLen = std::sqrt(x*x + y*y);
		return cachedLen;
	}

};

int main(int argc, char** argv)
{
	const Vector v{3.0, 4.0};

	std::cout << "length: " << v.GetLength() << std::endl;
	std::cout << "length: " << v.GetLength() << std::endl;	
}

