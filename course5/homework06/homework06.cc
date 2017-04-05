#include<iostream>
#include <cassert>
#include<cstring>
#include "string.h"

int main()
{
    String mystr1 = "hello";
    std::string str1 = "hello";
    assert(mystr1 == str1);
    assert(mystr1.length() == 5);

    String mystr2;
    std::string str2 = "";
    assert(mystr2 == str2);

    String mystr3 = "";
    assert(mystr3.length() == 0);

    String mystr4 = mystr1;
    assert(mystr4 == mystr1);

    String mystr5 = mystr3;
    assert(mystr5 == mystr3);

    mystr4 = "bye";
    std::string str4 = "bye";
    assert(mystr4 == str4);

    mystr5 = "";
    std::string str5 = "";
    assert(mystr5 == str5);

    mystr2 = std::move(mystr1);
    assert(mystr2 == "hello");

    mystr5 = std::move(mystr4);
    assert(mystr5 == "bye");

    String mystr6 = "good";
    assert(mystr6[2] == 'o');
    mystr6[2] = 'e';
    assert(mystr6 == "goed");

    const String mystr7 = "good";
    assert(mystr7[2] == 'o');

    String mystr8 =  mystr7 + " " +mystr5 + "!";
    assert(mystr8 == "good bye!");

    mystr2 += mystr8;
    assert(mystr2 == "hellogood bye!");

    mystr2 += "...";
    assert(mystr2 == "hellogood bye!...");
    std::cout << "mystr2 is: " << mystr2 << std::endl;
}
