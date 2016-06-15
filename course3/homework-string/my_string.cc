#include "my_string.h"

#include <cstring>
#include <stdexcept>

MyString::MyString(): mSize(0) { }

MyString::MyString(const char *inchar)
{
    this->mSize = std::strlen(inchar);
    this->mBuffer.reset(new char[this->mSize + 1]);
    std::strcpy(this->mBuffer.get(), inchar);
}

MyString::MyString(const MyString& str)
{
    if (!str.empty())
    {
        this->mSize = str.mSize;
        this->mBuffer.reset(new char[this->mSize + 1]);
        std::strcpy(this->mBuffer.get(), str.mBuffer.get());
    }
}

std::size_t MyString::size() const
{
    return this->mSize;
}

bool MyString::empty() const
{
    return !this->mBuffer || this->mSize == 0;
}

bool MyString::operator==(const MyString& other) const
{
    if (this->empty() && other.empty()) return true;
    if (this->empty() != other.empty()) return false;
    return std::strcmp(this->mBuffer.get(), other.mBuffer.get()) == 0;
}

bool MyString::operator!=(const MyString& other) const
{
    return !(*this == other);
}

const char& MyString::operator[](const std::size_t i) const
{
    if (i > this->mSize)
    {
        throw std::out_of_range("Index out of range");
    }
    return this->mBuffer[i];
}

char& MyString::operator[](const std::size_t i)
{
    if (i > this->mSize)
    {
        throw std::out_of_range("Index cannot be larger than the size of the string");
    }
    return this->mBuffer[i];
}

const char* MyString::c_str() const {
    if (!this->mBuffer) return "";
    return this->mBuffer.get();
}

void MyString::operator=(const char* inchar) {
    this->mSize = std::strlen(inchar);
    this->mBuffer.reset(new char[this->mSize + 1]);
    std::strcpy(this->mBuffer.get(), inchar);
}

MyString MyString::operator+(const MyString &other) const {
    auto str = MyString();
    str.mSize = this->mSize + other.mSize;
    str.mBuffer.reset(new char[str.mSize + 1]);
    std::strcpy(str.mBuffer.get(), this->mBuffer.get());
    std::strcpy(str.mBuffer.get() + this->mSize, other.mBuffer.get());
    return str;
}

MyString& MyString::operator+=(const MyString &other) {
    auto str = this->operator+(other);
    this->mSize = str.mSize;
    this->mBuffer.reset(new char[this->mSize + 1]);
    std::strcpy(this->mBuffer.get(), str.mBuffer.get());
    return *this;
}

MyString& MyString::operator=(const MyString &other) {
    this->mBuffer.reset(new char[other.mSize + 1]);
    std::strcpy(this->mBuffer.get(), other.c_str());
    return *this;
}

char* MyString::begin() {
    return this->mBuffer.get();
}

char* MyString::end() {
    return this->mBuffer.get() + this->mSize;
}

