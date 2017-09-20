#include "str.h"

int main()
{
    //Constructor
    Str s1 = "foo";
    std::cout << s1 << std::endl;

    //Copy Constructor
    Str s2 = s1;
    std::cout << s2 << std::endl;

    //Assignment operators
    s2 = "hello";
    std::cout << s2 << std::endl;
    s2 = Str("good");
    std::cout << s2 << std::endl;

    //operator[]
    Str s3 = "torning";
    s3[0] = 'm';
    std::cout << s3 << std::endl;

    for(int i = 0; i < s3.Size(); i++)
    {
        std::cout << s3[i] << std::endl;
    }

    //operator +
    Str str4 = s2 + s3;
    std::cout << str4 << std::endl;

    //operator +=
    Str str5 = "!!!";
    str4 += str5;
    str4 += "???";
    std::cout << str4 << std::endl;

    return 0;
}
