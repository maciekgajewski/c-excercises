#include <cstdio>
#include <string>
#include <sstream>

const int DEFAULT_PRECISION = 0;
const char* TRUE_STRING = "true";
const char* FALSE_STRING = "false";

void print(int value)
{
        std::printf("%d", value);
}

void print(unsigned int value)
{
        std::printf("%u", value);
}

void print(long int value)
{
        std::printf("%ld", value);
}

void print(unsigned long int value)
{
        std::printf("%lu", value);
}

void print(bool value)
{
        if (value) {
                std::printf(TRUE_STRING);
        } else {
                std::printf(FALSE_STRING);
        }   
}

void print(const char* const value )
{
        std::printf("%s", value);
}

void print(std::string value)
{
        print(value.c_str());
}

void print(double value, unsigned int precision=DEFAULT_PRECISION)
{
        std::ostringstream stringStream;
        stringStream << "%.";
        stringStream << precision;
        stringStream << 'f';
        std::printf(stringStream.str().c_str(), value);
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
