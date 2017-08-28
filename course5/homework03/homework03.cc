#include <cstdio>
#include <string>

void print(int val)
{
    std::printf("%i\n", val);
}

void print(bool val)
{
    std::printf("%s\n", val ? "true": "false");
}

void print(double val)
{
    std::printf("%g\n", val);
}

void print(double val, int precision)
{
    std::printf("%.*f\n", precision, val);
}

void print(std::string val)
{
    std::printf("%s\n", val.c_str());
}

void print(const char* val)
{
    std::printf("%s\n", val);
}

int main()
{
	// comment indicates the expected input
	print(7); // 7
	print(true);// true
	print(1.0/3.0, 2);// 0.33
	
	std::string s = "world!";
	print("hello, "); // hello, 
	print(s); // world!
	
	float f = 6;
	print(f); // 6
}

