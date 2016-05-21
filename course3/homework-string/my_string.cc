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

MyString::MyString(MyString&& str)
{
	if (!str.empty())
	{
		mBuffer.swap(str.mBuffer);
	}
}

bool MyString::empty() const
{
	return !mBuffer;
}

std::size_t MyString::size() const
{
	return empty() ? 0 : std::strlen(mBuffer.get());
}

const char* MyString::c_str() const
{
	return empty() ? "" : mBuffer.get();
}

MyString& MyString::operator=(const MyString& str)
{
	if (str.empty())
	{
		mBuffer.reset();
	}
	else
	{
		mBuffer.reset(new char[str.size() + 1]);
		std::strcpy(mBuffer.get(), str.mBuffer.get());
	}

	return *this;
}

MyString& MyString::operator=(MyString&& str)
{
	if (str.empty())
	{
		mBuffer.reset();
	}
	else
	{
		mBuffer.swap(str.mBuffer);
	}

	return *this;
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

MyString MyString::operator+(const MyString& str) const
{
	if (empty()) return str;
	else if (str.empty()) return *this;
	
	MyString retStr;
	retStr.mBuffer.reset(new char[size() + str.size() + 1]);
	std::strcpy(retStr.mBuffer.get(), mBuffer.get());
	std::strcpy(retStr.mBuffer.get() + size(), str.mBuffer.get());
	return retStr;
}

MyString& MyString::operator+=(const MyString& str)
{
	*this = *this + str;
	return *this;
}
