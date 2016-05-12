#include "my_string.h"
#include <cstring>


MyString::MyString(const char* str)
{
	if (str[0] != '\0')
	{
		mBuffer.reset(new char[std::strlen(str) + 1]);
		std::strcpy(mBuffer.get(), str);
	}
}

MyString::MyString(const MyString& str)
{
	if (!str.empty())
	{
		mBuffer.reset(new char[str.size() + 1]);
		std::strcpy(mBuffer.get(), str.mBuffer.get());
	}
}

bool MyString::empty() const
{
	return !mBuffer;
}

std::size_t MyString::size() const
{
	return mBuffer ? std::strlen(mBuffer.get()): 0;
}

bool MyString::operator==(const MyString& str) const
{
	if (empty() && str.empty()) return true;
	if (empty() || str.empty()) return false;

	return std::strcmp(mBuffer.get(), str.mBuffer.get()) == 0;
}

bool MyString::operator!=(const MyString& str) const
{
	return !operator==(str);
}

const char& MyString::operator[](int idx) const
{
	return mBuffer.get()[idx];
}

char& MyString::operator[](int idx)
{
	return mBuffer.get()[idx];
}