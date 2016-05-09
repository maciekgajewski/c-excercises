#pragma once
#include <iostream>
#include <memory>

class MyString
{
    private:
        //unique_ptr<char*> buf;

    public:
        MyString(const char* my_string) {
            std::cout << "Constructor" << std::endl;
            //buf = new char[strlen(my_string)];;
        }

        ~MyString() {
            std::cout << "Destructor" << std::endl;
        }
};
