#include <iostream>
#include <string>

struct S
{
	int i;
	double d;
};

const std::string* p = nullptr;

void print(const std::string& s)
{
	std::string copy = s;
	copy[0] = 'G';
	std::cout << copy << std::endl;
	p = &s;
}

int& a () {
	int y = 3;
	return y;
}

int main(int argc, char** argv)
{
	const char* s = "hello";
	const char c = s[0];
	
	std::string ss = s;
	ss[3] = 't';
	print("12345");
	
	print(*p);
}

