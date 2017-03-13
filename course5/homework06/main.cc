#include "simple_string.h"
#include <cassert>

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

int main(int, char**)
{
    using namespace simple_string;
    String s;
    assert(s.Length() == 0);
    s.Print();

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
    std::cout << s.Length() << std::endl;
    const char *cStr = s.CStr();
    std::cout << cStr << std::endl;

    int len = std::strlen(bonanza);
    for (auto i = 0; i <= len; i++)
    {
        assert(cStr[i] == bonanza[i]);
    }

    // assert(cStr == bonanza); // why does this fail?

    std::cout << s << std::endl;
    String emptyStr;
    std::cout << emptyStr << std::endl;
}
