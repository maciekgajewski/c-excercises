#include "simple_string.h"
#include <cassert>
#include <cstring>
#include <array>
#include <algorithm>
#include <iostream>

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
void test(const char* test_name, const StrT& s, const char* expected_content)
{
    int s_l = s.length();
    int expected_length = std::strlen(expected_content);
    bool strncmp_result = std::strncmp(s.c_str(), expected_content, std::min(s_l, expected_length));

    assert(s.length() == expected_length);
    assert(strncmp_result == 0);

    for (auto i = 0; i < expected_length; i++)
    {
        assert(s[i] == expected_content[i]);
    }

    std::cout << "Passed: " << test_name << std::endl;
}

template<typename StrT, typename StrT2>
void testEquality(const char* test_name, const StrT& s1, const StrT2& s2, bool are_equal)
{
    if (are_equal)
    {
        assert(s1 == s2);
        assert(s2 == s1);
    }
    else
    {
        assert(s1 != s2);
        assert(s2 != s1);
    }

    std::cout << "Passed: " << test_name << std::endl;
}

bool isA(const char& c)
{
    return std::strcmp(&c, "a");
}


int main(int, char**)
{
    using namespace simple_string;
    using namespace std::literals;

    /* Basic tests for construction and assignment */
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
            "CozyAssignER",
        }
    };

    for (auto i = 0; i < num_test_cases; i++)
    {
        test(test_names[i], inputs[i], expected_contents[i]);
    }

    /* Tests for concatenation */
    String concatStr = "Hello ";
    String concatToConstChar = concatStr + "World!";
    test("concat initialization w const char *", concatToConstChar, "Hello World!");

    String concatStr2 = "World Again!";
    String concatToString = concatStr + concatStr2;
    test("concat initialization w String", concatToString, "Hello World Again!");

    concatToString += " And again.";
    test("+= w const char *", concatToString, "Hello World Again! And again.");

    String concatStr3 = " And again twice.";
    concatToString += concatStr3;
    test("+= w String", concatToString, "Hello World Again! And again. And again twice.");

    /* Test out of bounds error with indexing */
    // String shortStr = "short";
    // const char *outcome;
    // const char *test_name;
    //
    // test_name = "index out of bounds";
    // try
    // {
    //     shortStr[1000];
    //     outcome = "Failed: ";
    // }
    // catch(...)
    // {
    //     outcome = "Passed: ";
    // }
    // std::cout << outcome << test_name << std::endl;
    //
    // test_name = "assignment to index out of bounds";
    // try
    // {
    //     shortStr[1000] = '8';
    //     outcome = "Failed: ";
    // }
    // catch(...)
    // {
    //     outcome = "Passed: ";
    // }
    // std::cout << outcome << test_name << std::endl;

    /* Test assignment & construction corner cases */
    /*
    Assign empty string to empty string
    Assign non-empty string to empty string
    Assign empty string to non empty string
    (repeat for copy/move, and construction)
    Check the content and the length after every operation.
    You can implement the test as one function, and array of input value and expected outputs.
    */
    String emptyStrCopyConstructed = "";
    String emptyStr;
    String emptyStr2;
    String emptyStrCopyConstructedFromString = emptyStr;
    String emptyStrMoveConstructedFromString = std::move(emptyStr2);
    String emptyStrMoveConstructedFromConstChar = std::move("");

    String emptyStrCopyAssigned;
    String emptyStrCopyAssignedFromString;
    emptyStrCopyAssigned = "";
    emptyStrCopyAssignedFromString = emptyStr;

    String nonEmptyStr = "I'm not empty.";
    String emptyStrToBeFilledWString;
    emptyStrToBeFilledWString = nonEmptyStr;
    String emptyStrToBeFilledWConstChar;
    emptyStrToBeFilledWConstChar = "I'm not empty either.";

    String nonEmptyStr2 = "I'm also not empty.";
    String emptyStrToBeMoveFilledWString;
    emptyStrToBeMoveFilledWString = std::move(nonEmptyStr2);
    String emptyStrToBeMoveFilledWConstChar;
    emptyStrToBeMoveFilledWConstChar = std::move("I'm also not empty either.");

    String anotherEmptyStr;
    nonEmptyStr2 = "I'm also not empty.";
    nonEmptyStr2 = anotherEmptyStr;

    const int num_test_cases_corner = 11;
    std::array<const char *, num_test_cases_corner> test_names_corner = {
        {
            "empty String w empty const char * copy construction",
            "empty String w empty String copy construction",

            "empty String w empty const char * move construction",
            "empty String w empty String move construction",

            "empty String w empty const char * copy assignment",
            "empty String w empty String copy assignment",

            "empty String w non-empty String copy assignment",
            "empty String w non-empty const char * copy assignment",

            "empty String w non-empty String move assignment",
            "empty String w non-empty const char * move assignment",

            "non-empty String w empty String copy assignment",
        }
    };
    std::array<String, num_test_cases_corner> inputs_corner = {
        {
            emptyStrCopyConstructed,
            emptyStrCopyConstructedFromString,

            emptyStrMoveConstructedFromConstChar,
            emptyStrMoveConstructedFromString,

            emptyStrCopyAssigned,
            emptyStrCopyAssignedFromString,

            emptyStrToBeFilledWString,
            emptyStrToBeFilledWConstChar,

            emptyStrToBeMoveFilledWString,
            emptyStrToBeMoveFilledWConstChar,

            nonEmptyStr2,
        }
    };
    std::array<const char *, num_test_cases_corner> expected_contents_corner = {
        {
            "", "",
            "", "",
            "", "",
            "I'm not empty.", "I'm not empty either.",
            "I'm also not empty.", "I'm also not empty either.",
            ""
        }
    };

    for (auto i = 0; i < num_test_cases_corner; i++)
    {
        test(test_names_corner[i], inputs_corner[i], expected_contents_corner[i]);
    }

    /* Equality tests */

    testEquality("two Strings are equal", String("same"), String("same"), true);
    testEquality("two std::strings are equal", "same"s, "same"s, true);
    testEquality("two Strings are different", String("same"), String("different"), false);
    testEquality("two std::strings are different", "same"s, "different"s, false);
    testEquality("Strings and const char * are equal", String("same"), "same", true);
    testEquality("std::strings and const char * are equal", "same"s, "same", true);
    testEquality("Strings and const char * are different", String("same"), "different", false);
    testEquality("std::strings and const char * are different", "same"s, "different", false);

    String iteratorTest = "this is a test";
    String iteratorTest2 = "this is another test";
    for (auto& elem: iteratorTest) {
        std::cout << elem << std::endl;
    }

    std::cout << std::boolalpha;
    auto any_a = std::any_of(iteratorTest.begin(), iteratorTest.end(), isA);
    assert (any_a);

    bool are_equal = std::equal(iteratorTest.begin(), iteratorTest.end(), iteratorTest2.begin());
    assert (!are_equal);

    auto max_el = std::max_element(iteratorTest.begin(), iteratorTest.end(), std::greater<char>());
    auto max_el_index = std::distance(iteratorTest.begin(), max_el);
    int index_first_space = 4;
    assert (max_el_index == index_first_space);

    char t = 't';
    int num_t = std::count(iteratorTest.begin(), iteratorTest.end(), t);
    assert (num_t == 3);

    std::sort(iteratorTest.begin(), iteratorTest.end(), std::greater<char>());
    assert (iteratorTest == "tttsssiihea   ");

    std::reverse(iteratorTest.begin(), iteratorTest.end());
    assert (iteratorTest == "   aehiisssttt");
}
