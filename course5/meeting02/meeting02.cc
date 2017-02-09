#include <iostream>

int main(int argc, char** argv)
{
	const int i = 6;
	int* p = const_cast<int*>(&i);
	
	std::cout << "&i = " << &i << std::endl;
	std::cout << "p = " << p << std::endl;
	
	float f = 6.66;
	const float* cpf = &f;
	float* pf = &f;
	
	*p = 77;
	*pf = 88.88;
	
	std::cout << "i= " << i << std::endl;
	std::cout << "*p= " << *p << std::endl;
	std::cout << "f= " << f << std::endl;
	
}

