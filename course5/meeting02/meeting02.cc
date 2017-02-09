#include <iostream>

struct S
{
};

int main(int argc, char** argv)
{
	int i = 6;
	int* p = &i;
	
	float f = 6.66;
	float* pf = &f;
	
	*p = 77;
	*pf = *p; // convertion int -> float
	
	float* p2 = reinterpret_cast<float*>(&i);
	
	//*p2 = 77;
	
	//S s = *p2;
	
	std::cout << "i= " << i << std::endl;
	std::cout << "*p2= " << *p2 << std::endl;
	std::cout << "f= " << f << std::endl;
}

