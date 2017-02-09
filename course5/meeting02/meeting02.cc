#include <iostream>

int main(int argc, char** argv)
{
	int i1 = 5;
	const int ci = 6;
	int* p1 = &i1;
	const int* p2 = &ci;
	p2 = p1;
	p1 = p2;
	auto t = *p1;
	
	void* vp = p1;
	
	std::cout << "t=" << t << std::endl;
	
}

