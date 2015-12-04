#include <iostream>
#include <string>

int factorial(int x)
{
	std::cout << "&x=" << &x << ", x=" << x << std::endl;
	if (x == 0) 
		return 1;
	else
		return x * factorial(x-1);
}

void test(int y)
{
	int z = y+6;
	std::cout << "&z=" << &z << std::endl;
}

struct S
{
	int mI;
	double mD;
};

int main()
{
	int r = factorial(3);
	int t = factorial(2);
	
	std::string s = "Hello!oijfijaifja'pkjfpsajfjf'jfpwae"; // std::string::operator=(const char*)
	std::cout << "r=" << r << std::endl;
	std::cout << "size of s=" << sizeof(s) << std::endl;

	// ~std::string
}


bool CheckPassword(const std::string& password)
{
	return std::strcmp(password, "secret") == 0;
	return std::string(password) == "secret"; // std::string::operator==(string, const char*)
	return password == "secret";
	
}
