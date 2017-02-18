#include <cstdio>
#include <string>

void print(int i)
{
    std::printf("%d", i);
}

void print(bool b)
{
    std::printf(b ? "true" : "false");
}

void print(double d)
{
    std::printf("%lg", d);
}

void print(double d, unsigned precision)
{
    std::printf("%.*lf", precision, d);
}

void print(const char *str)
{
    std::printf("%s", str);
}

void print(const std::string &s)
{
    std::printf("%s", s.c_str());
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
