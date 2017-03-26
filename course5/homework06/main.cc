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

    assert(strncmp_result == 0);
    assert(s.length() == expected_length);

    std::cout << "Passed: " << test_name << std::endl;
}


int main(int, char**)
{
    using namespace simple_string;
    using namespace std::literals;

    String defaultS;
    const int num_test_cases = 1;
    std::array<const char *, num_test_cases> test_names = { {"default constructor"} };
    std::array<String, num_test_cases> inputs = { {defaultS} };
    std::array<const char *, num_test_cases> expected_contents = { {""} };
    std::array<int, num_test_cases> expected_lengths = { {0} };


    for (auto i = 0; i < num_test_cases; i++)
    {
        test(test_names[i], inputs[i], expected_contents[i], expected_lengths[i]);
    }

    String s;

    String sFromChar = "word";
    sFromChar.Print();

    String copyConstructedString = sFromChar;
    copyConstructedString.Print();
    sFromChar.Print();

    String moveConstructedString = std::move(sFromChar);
    moveConstructedString.Print();

    String assignmentTester = "yolo";
    assignmentTester.Print();
    assignmentTester = moveConstructedString;
    assignmentTester.Print();
    moveConstructedString.Print();

    assignmentTester = std::move(moveConstructedString);
    assignmentTester.Print();
    moveConstructedString.Print();

    assignmentTester = "yolo";
    assignmentTester.Print();

    for (auto i = 0; i < 4; i++)
    {
        assert(assignmentTester[i] == "yolo"[i]);
    }
    assignmentTester.Print();

    // How could I use assert to test this one?
    // assignmentTester[5]; // should raise runtime error

    for (auto i = 0; i < 4; i++)
    {
        assignmentTester[i] = "word"[i];
    }
    assignmentTester.Print();
    for (auto i = 0; i < 4; i++)
    {
        assert(assignmentTester[i] == "word"[i]);
    }
    assignmentTester.Print();

    // assignmentTester[5] = 'c'; // should raise runtime error

    String concatTester1 = "Hello ";
    String concatTester2 = concatTester1 + "World!";
    concatTester2.Print();
    concatTester1.Print();

    String concatTester3 = "World Again!";
    String concatTester4 = concatTester1 + concatTester3;
    concatTester4.Print();

    concatTester4 += " And again.";
    concatTester4.Print();

    String concatTester5 = " And again twice.";
    concatTester4 += concatTester5;
    concatTester4.Print();

    const char *bonanza = "bonanza";
    s = bonanza;
    std::cout << bonanza << std::endl;
    std::cout << s.length() << std::endl;
    const char *c_str = s.c_str();
    std::cout << c_str << std::endl;

    int len = std::strlen(bonanza);
    for (auto i = 0; i <= len; i++)
    {
        assert(c_str[i] == bonanza[i]);
    }

    // assert(c_str == bonanza); // why does this fail?

    std::cout << s << std::endl;
    String emptyStr;
    std::cout << emptyStr << std::endl;
}
