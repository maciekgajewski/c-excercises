// Example program
#include <string>
#include <cstdio>

void print(std::string value)
{
	std::printf("%s", value.c_str());
}

void print(bool value)
{
	std::printf("%s", value ? "true" : "false");
}

void print(int value)
{
	std::printf("%d", value);
}

void print(float value, uint precision = 0)
{
    	std::string format = std::string("%.") + std::to_string(precision).c_str() + std::string("f");
	std::printf(format.c_str(), value);
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

