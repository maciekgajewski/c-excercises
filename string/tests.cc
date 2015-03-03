#include "string.h"

#include <cassert>
#include <iostream>
#include <string>
#include <cstring>
#include <vector>
#include <algorithm>
#include <iterator>
#include <sstream>

void test_default_construction()
{
    String s;
	
    assert(s.size() == 0 && "Default-constructed String should have size=0");
    assert(s.empty() && "Default constructed String should be empty");
	
    assert(s.c_str() != nullptr && "Even default constructed String should return usable c-string");
    assert(std::strlen(s.c_str()) == 0 && "c-string returned by default-constructed String should be empty");
}

//String IntToString(int i)
//{
//    std::string asInt = std::to_string(i);
	
//    // use range-based initialization
//    String s(asInt.begin(), asInt.end());
//    return s;
//}

void test_initialization()
{
    // from c-string
	
    String a("abcd");
	
    assert(a == "abcd");
	
    // copy-construction
    String b(a);
	
    assert(b == a);
    assert(b == "abcd");
	
    // move-construction, range construction
    //String c(IntToString(7));
	
    //assert(c == "7");
}

void test_writable_iterators()
{
    String s("abc");
	
    for(char& c : s)
    {
        c = 'x';
    }
	
    assert(s == "xxx");
}

void test_read_only_iterators()
{
    const String s("qwert");
	
    // copy the content of string to vector
    std::vector<char> v;
    v.reserve(s.size());
    std::copy(s.begin(), s.end(), std::back_inserter(v));
	
    assert(v.size() == s.size());
	
    // compare
    bool eq = std::equal(s.begin(), s.end(), v.begin());
    assert(eq);
	
}

void test_streaming_operator()
{
    const String s("12345");
	
    std::ostringstream ss;
	
    ss << s;
	
    assert(ss.str() == "12345");
}

void test_concatenation()
{
    String a("aaa");
    String b("bbb");
    String c = a + b;
    std::cout << "c = " << c << std::endl;
}

// TODO add more tests here. Achieve 100% test coverage

int main()
{
    test_default_construction();
    test_initialization();
    test_writable_iterators();
    test_read_only_iterators();
    test_streaming_operator();
    test_concatenation();
	
    std::cout << "All OK" << std::endl;

}
