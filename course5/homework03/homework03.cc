#include <string>
#include <cstdio>

void print(int value)
{
	std::printf("%d\n", value);
}

void print(std::string value)
{
	std::printf("%s\n", value.c_str());
}

void print(bool value)
{
	value ? std::printf("true\n") : std::printf("false\n");
}

// The ANSI C standard specifies that the default precision is 6
void print(double value, int precision=6)
{
	std::printf("%.*f\n", precision, value);
}

int main()
{
	// comment indicates the expected input
	print(7); // 7
	print(true);// true
	print(1.0/3.0, 2);// 0.33

	std::string s = "world!";
	print("hello, ") // hello, 
	print(s); // world!

	float f = 6;
	print(f); // 6
}

