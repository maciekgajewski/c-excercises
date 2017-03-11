#include "string.h"
#include <assert.h>

int main(int, char**)
{

    course::string s1 = "hello";
    assert(s1 == "hello");
    assert(s1.length() == 5);
    course::string s2 = s1;
    assert( s1 == s2 );
    s1 = "world";
    assert( ! (s1 == s2) );
    std::cout << s1[1] << std::endl;
    std::cout << s1 << std::endl;
    assert( s1[2] == 'r');
    s1[2] = 'p';
    assert( s1[2] == 'p');
    course::string s3;
    s3 = s1 + s2;
    assert( s3 == "wopldhello");
    s3 += s1;
    assert( s3 == "wopldhellowopld");
    std::cout << s3.c_str() << std::endl;
    s1 = std::move(s3);
    assert( s1 == "wopldhellowopld");
}