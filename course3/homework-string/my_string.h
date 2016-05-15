#pragma once
#include <iostream>
#include <memory>

class MyString
{
private:
    std::size_t length;
    std::unique_ptr<char []> buff;

public:
    MyString() {
        length = 0;
    }

    MyString(const char *data) {
        length = std::strlen(data);

        buff = std::make_unique<char []>(length + 1);        

        std::strcpy(buff.get(), data);
    }

    MyString(const MyString& rhs) {
        length = rhs.size();
        if (rhs.buff.get()) {
            buff = std::make_unique<char []>(length + 1);        
            std::strcpy(buff.get(), rhs.buff.get());
        }
    }

    bool empty() const {
       return length == 0 ? true : false;
    }

    std::size_t size() const {
        return length;
    }

    bool operator!=(const MyString& rhs) {
        return !operator==(rhs);
    }

    bool operator==(const MyString& rhs) {
        if (buff.get() && rhs.buff.get())
            return std::strcmp(buff.get(), rhs.buff.get()) == 0;
        // if this or rhs is null this will return false
        return buff.get() == rhs.buff.get() ? true : false;
    }

    char& operator[](int index) {
        return buff[index];
    }

    char& operator[](int index) const {
        return buff[index];
    }
};
