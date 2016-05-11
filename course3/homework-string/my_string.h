#pragma once
#include <iostream>
#include <memory>

class MyString
{
private:
    int length;
    std::unique_ptr<char []> buff;

public:
    MyString() {
        length = 0;
    }

    MyString(const char *data) {
        length = std::strlen(data);

        buff = std::make_unique<char []>(length);        

        std::strcpy(buff.get(), data);
    }

    MyString(const MyString& rhs) {
        length = rhs.size();
        buff = std::make_unique<char []>(length);        
        std::strcpy(buff.get(), rhs.buff.get());
    }

    bool empty() const {
       return length == 0 ? true : false;
    }

    int size() const {
        return length;
    }

    bool operator!=(const MyString& rhs) {
        return !operator==(rhs);
    }

    bool operator==(const MyString& rhs) {
        return std::strcmp(buff.get(), rhs.buff.get()) == 0;
    }

    char& operator[](int index) {
        return buff[index];
    }

    char& operator[](int index) const {
        return buff[index];
    }
};
