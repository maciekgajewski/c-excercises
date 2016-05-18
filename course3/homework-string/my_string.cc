#include "my_string.h"

#include <cstring>
#include <stdexcept>

MyString::MyString(): mSize(0) { }

MyString::MyString(const char *inchar) :mSize(std::strlen(inchar)), mBuffer(new char[mSize + 1])
{
	std::strcpy(mBuffer.get(), inchar);
}

MyString::MyString(const std::size_t size) :mSize(size), mBuffer(new char[mSize + 1])
{
}

MyString::MyString(const MyString& str)
{
	if (!str.empty())
	{
		mSize = str.mSize;
		mBuffer.reset(new char[mSize + 1]);
		std::strcpy(mBuffer.get(), str.mBuffer.get());
	}
}

std::size_t MyString::size() const
{
	return mSize;
}

bool MyString::empty() const
{
	return !mBuffer || mSize == 0;
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

char& MyString::operator[](const std::size_t i) const
{
	if (i > mSize)
	{
		throw std::out_of_range("Index cannot be larger than the size of the string");
	}
	return mBuffer[i];
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
	auto str = MyString(this->mSize + other.mSize);
	std::strcpy(str.mBuffer.get(), this->mBuffer.get());
	std::strcpy(str.mBuffer.get() + this->mSize, other.mBuffer.get());
	return str;
}

MyString& MyString::operator+=(const MyString &other) {
	auto current_size = this->mSize;
	this->mSize = current_size + other.mSize;
	auto current = this->c_str();
	this->mBuffer.reset(new char[this->mSize + 1]);
	std::strcpy(this->mBuffer.get(), current);
	std::strcpy(this->mBuffer.get() + current_size, other.c_str());
	return *this;
}

MyString& MyString::operator=(const MyString &other) {
	this->mBuffer.reset(new char[other.mSize + 1]);
	std::strcpy(this->mBuffer.get(), other.c_str());
	return *this;
}











