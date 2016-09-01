#include <iostream>

void print(int x) { std::cout << "int=" << x << std::endl; }
void print(float x) { std::cout << "float=" << x << std::endl; }

int main(int argc, char** argv)
{
	int i = 7;
	float f = 7;
	
	int* p = &i;
	float* r = reinterpret_cast<float*>(&i);
	
	print(i);
	print(f);
	print(*p);
	print(*r);
	
}

