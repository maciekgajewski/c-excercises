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

        for (int i = 0; i < length; i++)
            buff[i] = data[i];
    }

    MyString(const MyString& rhs) {
        length = rhs.size();
        buff = std::make_unique<char []>(length);        
        for (int i = 0; i < length; i++)
            buff[i] = rhs[i];
    }

    bool empty() const {
       return length == 0 ? true : false;
    }

    bool empty() {
        return length == 0 ? true : false;
    }

    int size() const {
        return length;
    }

    int size() {
        return length;
    }

    bool operator!=(const MyString& rhs) {
        return !operator==(rhs);
    }

    bool operator==(const MyString& rhs) {
//        return std::strcmp(buff, rhs);
        if (length != rhs.size())
            return false;
        for (int i = 0; i < length; i++)
            if (buff[i] != rhs[i])
                return false;
        return true;
    }

    char& operator[](int index) {
        return buff[index];
    }

    char& operator[](int index) const {
        return buff[index];
    }
};
