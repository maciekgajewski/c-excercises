#include <iostream>
#include <cstring>
#include "my_string.h"

MyString::MyString(){}

MyString::MyString(const char* argString)
{
        buffer = std::unique_ptr<char[]>(new char[ std::strlen(argString) + 1]);
        std::strcpy(buffer.get(), argString);;
}

MyString::MyString(const MyString& argString)
{
        *this = argString;
}


MyString::MyString(MyString&& argString){
        *this = std::move(argString);
}

const bool MyString::empty() const
{
        if (buffer){
                return buffer[0] == '\0' || buffer[0] == ' ';
        }
        else return true;
}

const size_t MyString::size() const
{
        if (buffer){
                return std::strlen(buffer.get());
        }
        else return 0;
}

const char* MyString::c_str() const
{
        if (buffer){
                return buffer.get();
        }
        else {
            char* r = new char('\0');
            return r;
        }
}

const bool MyString::operator == (const MyString& argString) const
{
        if (buffer && argString.buffer){
                return std::strcmp(buffer.get(), argString.buffer.get()) == 0 ;
        }
        else if ( buffer == nullptr && argString.buffer == nullptr ){
                return true;
        }
        else return false;
}

const bool MyString::operator != (const MyString& argString) const
{
        if ( buffer && argString.buffer){
                if ( *this == argString ){
                        return false;
                }
                else return true;
        }
        else if ( buffer == nullptr && argString.buffer == nullptr ){
                return false;
        }
        else return false;
}

const bool MyString::operator< (const MyString& argString) const
{
        if (buffer == nullptr && argString.buffer == nullptr){
            return false;
        }
        else if (buffer && argString.buffer == nullptr ){
            return false;
        }
        else if ( buffer == nullptr && argString.buffer){
            return true;
        }
        else {
            return std::strcmp(buffer.get(), argString.buffer.get()) < 0;
        }

}

char& MyString::operator[](size_t index) const
{
        return buffer[index];
}


MyString& MyString::operator = (const MyString& argString)
{
        //std::cout << "Assignment operator invoked, value: " << argString.c_str() << std::endl;
        if (argString.empty()){
                buffer.release();
        }
        else {
                buffer = std::unique_ptr<char[]>(new char[argString.size()+1]);
                std::strcpy(buffer.get(), argString.buffer.get());
        }
        return *this;
}

MyString& MyString::operator = (MyString&& argString)
{
        //std::cout << "Move operator invoked, value: " << argString.c_str() << std::endl;
        if (argString.empty()){
                buffer.release();
        }
        else {
                buffer = std::move(argString.buffer);
        }
        return *this;
}

MyString MyString::operator + (const MyString& argString) const
{
        MyString returnString;
        if (buffer == nullptr && argString.buffer == nullptr){
            return returnString;
        }
        else if (buffer && argString.buffer == nullptr ){
                returnString = *this;
        }
        else if ( buffer == nullptr && argString.buffer){
            returnString.buffer = std::unique_ptr<char[]>(new char[argString.size() + 1]);
            std::strcpy(returnString.buffer.get(), argString.buffer.get());
        }
        else{
                returnString.buffer = std::unique_ptr<char[]>(new char[size() + argString.size() + 1]);
                std::strcpy(returnString.buffer.get(), buffer.get());
                std::strcat(returnString.buffer.get(), argString.buffer.get());
        }
        return returnString;
}

MyString& MyString::operator += (const MyString& argString)
{
        if (buffer && argString.buffer){
            *this = *this + argString;
            return *this;
        }
        else if (!buffer && !argString.buffer){
            return *this;
        }
        else if (buffer && !argString.buffer){
            return *this;
        }
        else {
            std::strcpy(buffer.get(), argString.buffer.get());
            return *this;
        }
}


                
    
