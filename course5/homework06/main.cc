#include "simple_string.h"
#include <cassert>
#include <cstring>
#include <array>
#include <algorithm>

/***
Please, write a String class.

String is the simplest container; it manages a char buffer.
Use std::unique_ptr<char[]> to manage your buffer.

As before, split your implementation into 3 files, and make sure to test all the methods/operators/constructors. Attempt to automate your tests, ie instead of printing them and require eyeball checking, let the computer do the testing; use asserts.

Implement the following operations:
- Default constructor (ideally, in well behaving container, default constructor is cheap and doesn’t allocate memory)
- Copy constructor and assignment operator. The copy should be deep; make sure it is deep.
- Move constructor and assignment operator.
- Constructor and assignment operator from const char*
- length() method
- operator[], to access individual characters. Both const and non-const version. Test both!
- Operators + and += for concatenation
- c_str() method
- operator<< for stream output.

Use std::string as an inspiration. Ideally, your string should be source-compatible with std::string, ie, replacing your String with std::string should yield the same behavior.
Run your program through valgrind, make sure there is no memory leaks and no errors.
***/

template<typename StrT>
void test(const char* test_name, const StrT& s, const char* expected_content, int expected_length)
{
    int s_l = s.length();
    int content_l = std::strlen(expected_content);
    bool strncmp_result = std::strncmp(s.c_str(), expected_content, std::min(s_l, content_l));

    assert(s.length() == expected_length);
    assert(strncmp_result == 0);

    for (auto i = 0; i < expected_length; i++)
    {
        assert(s[i] == expected_content[i]);
    }

    std::cout << "Passed: " << test_name << std::endl;
}


int main(int, char**)
{
    using namespace simple_string;
    using namespace std::literals;

    String defaultS;
    String sFromChar = "word";
    String copyConstructed = sFromChar;

    String toBeAssigned = "movetest";
    String moveConstructed = std::move(toBeAssigned);

    toBeAssigned = "assignment";
    String copyAssigner = "CopyAssignER";
    String moveAssigner = "MoveAssignER";
    String copyAssigned;
    copyAssigned = copyAssigner;
    String moveAssigned;
    moveAssigned = std::move(moveAssigner);

    copyAssigner[2] = 'z';

    const int num_test_cases = 8;
    std::array<const char *, num_test_cases> test_names = {
        {
            "default constructor",

            "const char * construction",
            "copy construction",
            "move construction",

            "const char * assignment",
            "copy assignment",
            "move assignment",

            "[] assignment"
        }
    };
    std::array<String, num_test_cases> inputs = {
        {
            defaultS,
            sFromChar, copyConstructed, moveConstructed,
            toBeAssigned, copyAssigned, moveAssigned,
            copyAssigner
        }
    };
    std::array<const char *, num_test_cases> expected_contents = {
        {
            "",
            "word", "word", "movetest",
            "assignment", "CopyAssignER", "MoveAssignER",
            "CozyAssignER"
        }
    };
    std::array<int, num_test_cases> expected_lengths = {
        {
            0,
            4, 4, 8,
            10, 12, 12,
            12
        }
    };

    for (auto i = 0; i < num_test_cases; i++)
    {
        test(test_names[i], inputs[i], expected_contents[i], expected_lengths[i]);
    }

    String shortStr = "short";
    const char *outcome;
    const char *test_name;

    test_name = "index out of bounds";
    try
    {
        shortStr[1000];
        outcome = "Failed: ";
    }
    catch(...)
    {
        outcome = "Passed: ";
    }
    std::cout << outcome << test_name << std::endl;

    test_name = "assignment to index out of bounds";
    try
    {
        shortStr[1000] = '8';
        outcome = "Failed: ";
    }
    catch(...)
    {
        outcome = "Passed: ";
    }
    std::cout << outcome << test_name << std::endl;

    //
    // String concatTester1 = "Hello ";
    // String concatTester2 = concatTester1 + "World!";
    // concatTester2.Print();
    // concatTester1.Print();
    //
    // String concatTester3 = "World Again!";
    // String concatTester4 = concatTester1 + concatTester3;
    // concatTester4.Print();
    //
    // concatTester4 += " And again.";
    // concatTester4.Print();
    //
    // String concatTester5 = " And again twice.";
    // concatTester4 += concatTester5;
    // concatTester4.Print();
    //
    // const char *bonanza = "bonanza";
    // s = bonanza;
    // std::cout << bonanza << std::endl;
    // std::cout << s.length() << std::endl;
    // const char *c_str = s.c_str();
    // std::cout << c_str << std::endl;
    //
    // int len = std::strlen(bonanza);
    // for (auto i = 0; i <= len; i++)
    // {
    //     assert(c_str[i] == bonanza[i]);
    // }
    //
    // // assert(c_str == bonanza); // why does this fail?
    //
    // std::cout << s << std::endl;
    // String emptyStr;
    // std::cout << emptyStr << std::endl;
    //
    // auto test = "hello"s;
    // auto test2 = "hello"s;
    // // bool eq = test.c_str() == test2.c_str();
    // bool eq2 = std::strncmp(test.c_str(), "hello", test.length());
    // std::cout << "equality? " << eq2 << std::endl;
}
