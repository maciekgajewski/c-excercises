#pragma once
#include <iostream>
#include <memory>
#include <boost/functional/hash.hpp>

class MyString
{
private:
    std::size_t length;
    std::unique_ptr<char []> buff;

public:
    MyString() : length(0) {}
    
    MyString(const char *data) : length(0), buff() {
        length = std::strlen(data);

        buff = std::make_unique<char []>(length + 1);        

        std::strcpy(buff.get(), data);
    }

    MyString(const MyString& rhs) : length(0), buff() {
        length = rhs.size();
        if (rhs.buff.get()) {
            buff = std::make_unique<char []>(length + 1);        
            std::strcpy(buff.get(), rhs.buff.get());
        }
    }

    MyString(MyString&& rhs) : length(rhs.size()), buff(std::move(rhs.buff)) { }

    bool empty() const {
        return length == 0;
    }

    std::size_t size() const {
        return length;
    }

    const char* begin() const {
        return buff.get();
    }

    const char* end() const {
        return buff.get() + size();
    }

    const char* c_str() const {
        if (buff)
            return buff.get();
        else
            return "";
    }

    MyString& operator=(const MyString& rhs) {
        if (rhs.empty()) {
            buff.reset();
        }
        else {
            buff = std::make_unique<char []>(rhs.length + 1);
            std::strcpy(buff.get(), rhs.buff.get());
            length = rhs.length;
        }
        return *this;
    }

    MyString& operator=(MyString&& rhs) {
        buff = std::move(rhs.buff);
        length = rhs.length;
        return *this;
    }

    MyString operator+(const MyString& rhs) const {
        MyString res(*this);
        res += rhs;
        return res;
    }

    MyString& operator+=(const MyString& rhs) {
        if (!rhs.empty()) {
            std::size_t currentSize = size();
            std::unique_ptr<char []> temp = std::make_unique<char []>(currentSize + rhs.size() + 1);
            if (size())
                std::strcpy(temp.get(), buff.get());
            if (rhs.size())
                std::strcpy(temp.get() + currentSize, rhs.buff.get());
            buff.swap(temp);
            length += rhs.size();
        }

        return *this;
    }

    bool operator<(const MyString& rhs) {
        if (!buff)
            return true;
        if (!rhs.buff)
            return false;
        return strcmp(buff.get(), rhs.buff.get()) <= 0;
    }

    bool operator!=(const MyString& rhs) const {
        return !operator==(rhs);
    }

    bool operator==(const MyString& rhs) const {
        if (buff.get() && rhs.buff.get())
            return std::strcmp(buff.get(), rhs.buff.get()) == 0;
        // if this or rhs is null this will return false
        return buff.get() == rhs.buff.get();
    }

    char& operator[](int index) {
        return buff[index];
    }

    char& operator[](int index) const {
        return buff[index];
    }
};

template<>
struct std::hash<MyString> {
    std::size_t operator()(const MyString& str) const {
        std::size_t seed = 0;
        for (int i = 0; i < str.size(); i++)
            boost::hash_combine(seed, str[i]);
        return seed;
    }
};

