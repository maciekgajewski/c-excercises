#include "my_string.h"

#include <cstring>
#include <memory>

MyString::MyString() 
	:
	mBuffer(nullptr)
{
}

MyString::MyString(const MyString& that)
{
	if (that.empty())
	{
		mBuffer = nullptr;
	}
	else
	{
		mBuffer = std::make_unique<char[]>(std::strlen(that.mBuffer.get()) + 1);
		std::strcpy(mBuffer.get(), that.mBuffer.get());
	}
}

MyString::MyString(const char* str)
{
	if (str == nullptr || str[0] == '\0')
	{
		mBuffer = nullptr;
	}
	else
	{
		mBuffer = std::make_unique<char[]>(std::strlen(str) + 1);
		std::strcpy(mBuffer.get(), str);
	}
}

MyString& MyString::operator= (const MyString& that)
{
	if (this == &that)
		return *this;
	
	if (that.empty())
	{
		mBuffer = nullptr;
	}
	else
	{
		mBuffer = std::make_unique<char[]>(std::strlen(that.mBuffer.get()) + 1);
		std::strcpy(mBuffer.get(), that.mBuffer.get());
	}

	return *this;
}


MyString MyString::operator+(const MyString& that) const
{
	auto length = size() + that.size();

	if (length == 0)
		return MyString();
	else
	{
		// FIXME:
		return MyString();
	}
}

bool MyString::empty() const
{
	return mBuffer == nullptr || mBuffer[0] == '\0';
}

int MyString::size() const
{
	return empty() ? 0 : std::strlen(mBuffer.get());
}

bool MyString::operator==(const MyString& that) const
{
	if (empty() && that.empty())
		return true;

	if (empty() != that.empty())
		return false;

	return std::strcmp(mBuffer.get(), that.mBuffer.get()) == 0;
}

bool MyString::operator!=(const MyString& that) const
{
	return !operator==(that);
}

const char&	MyString::operator[](int index) const
{
	return mBuffer[index];
}

char& MyString::operator[](int index)
{
	return mBuffer[index];
}


const char* MyString::c_str() const
{
	return mBuffer.get();
}