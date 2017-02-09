#include <iostream>

int fun()
{
	int i;
	if (i == 42)
		return 1;
	else
		return 7;
}

int main(int argc, char** argv)
{
	std::cout << "Hello again!" << std::endl;

	float x = 7;
	int y;
	int g = 88;
	
	auto p = &y; // int*
	y = 5;
	
	const int z = y;
	//z = 4; ERROR
	auto p2 = &z; // const int*
	//*p2 = 6; ERROR
	p2 = &y;
	
	int* const p3 = &y;
	*p3 = 8;
	//p3 = &g;// ERROR
	
	std::cout << "y=" << y << std::endl;
	std::cout << "p==p2 " << std::boolalpha << (p == p2) << std::endl;
	std::cout << "p==p3 " << (p == p3) << std::endl;
	
	
}

