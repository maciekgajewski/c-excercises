#ifndef MY_STRING_H
#define MY_STRING_H
#include<iostream>
#include<memory>
#include<cstring>

class MyString
{
    public:

        MyString();
        MyString(const char*);
        MyString(const MyString&);

        std::size_t size() const;
        bool empty() const;
        const char* c_str() const;

        bool operator==(const MyString& other) const;
        bool operator!=(const MyString& other) const;

        char operator[](std::size_t index) const;
        char& operator[](std::size_t index);

        MyString& operator=(const MyString& other);
        MyString& operator=(const char*);

        MyString& operator+=(const MyString& other);
        MyString& operator+=(const char* other);

        MyString operator+(const MyString& other) const;
        MyString operator+(const char* other) const;

    private:
        std::unique_ptr<char[]> mBuffer;
        void clearBuffer();
};

#endif // MY_STRING_H
