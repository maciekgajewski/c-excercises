#include <iostream>
//#include <stdint>
#include <limits>

void print(int x) { std::cout << "int=" << x << std::endl; }
void print(float x) { std::cout << "float=" << x << std::endl; }

int main(int argc, char** argv)
{
	int i = 7;
	std::int8_t c = 8;
	std::uint8_t uc = 8;
	std::int64_t ll = 334455;
	
	std::cout << "Max value of int = " << std::numeric_limits<int>::max() << std::endl;
	
	double f = 7;
	
	int* p = &i;
	double* r = reinterpret_cast<float*>(&i);
	
	print(i);
	print(f);
	print(*p);
	print(*r);
	
}

