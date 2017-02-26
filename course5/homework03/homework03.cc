#include <cstdio>
#include <iostream>

// TODO your code goes here

void print(int number)
{
    printf("%d\n",number);
}

void print(bool boolean)
{
    printf("%s\n", boolean ? "true":"false");
}

void print(float number, int precision=0)
{
    printf("%.*f\n", precision, number);
}

void print(const char* str)
{
    printf("%s", str);
}

void print(const std::string &str)
{
    printf("%s\n", str.c_str());
}


int main(int /*argc*/, char** /*argv*/)
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

