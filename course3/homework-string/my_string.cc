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

