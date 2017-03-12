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
    // static_assert(s.Length() == 0, "Default constructor should not allocate memory");
    std::cout << s.Length() << std::endl;
    s.Print();


    std::unique_ptr<char[]> p = std::make_unique<char[]>(5);
    for(int i = 0; i < 4 ; i++)
    {
        p[i] = 'y';
    }
    for(int i = 0; i < 3 ; i++)
    {
        std::cout << p[i] << std::endl;
    }
    p[0] = 'y';
    p[1] = 'o';
    p[2] = 'l';
    p[3] = 'o';

    std::cout << *p.get() << std::endl;

    // int y = 0;
    // int * ptr = &y;
    // *ptr = 8;
    //
    // std::cout << *ptr << std::endl;

    char thechars[] = "chars";
    std::cout << thechars << std::endl;

    // char thechars2[] = *p;
    // std::cout << thechars2 << std::endl;
    std::unique_ptr<int[]> int_p = std::make_unique<int[]>(5);


    const char* word = "word";
    std::cout << std::strlen(word) << std::endl;

    String sFromChar = String(word);
    sFromChar.Print();

    String copyConstructedString = sFromChar;
    copyConstructedString.Print();
    sFromChar.Print();

    String moveConstructedString = std::move(sFromChar);
    moveConstructedString.Print();

    String assignmentTester = String(word);
    assignmentTester = moveConstructedString;
    assignmentTester.Print();
    moveConstructedString.Print();

    assignmentTester = std::move(moveConstructedString);
    assignmentTester.Print();
    moveConstructedString.Print();
}
