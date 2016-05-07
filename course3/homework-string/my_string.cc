#include "my_string.h"

#include <cstring>
#include <memory>

MyString::MyString() 
	:
	mLength(0),
	mBuffer(nullptr)
{
}

MyString::MyString(const MyString& that) 
	: MyString::MyString(that.mBuffer.get(), that.mLength)
{
}

MyString::MyString(const char* source)
	: MyString::MyString(source, std::strlen(source))
{
}

MyString::MyString(const char* source, const int length)
	:
	mLength(length),
	mBuffer(new char[length + 1]) // +1 to allow for the '\0' terminator
{
	std::strcpy(mBuffer.get(), source);
}

bool MyString::empty() const
{
	return mLength == 0;
}

int MyString::size() const
{
	return mLength;	
}

bool MyString::operator==(const MyString& that) const
{
	return mLength == that.mLength
		   && std::strcmp(mBuffer.get(), that.mBuffer.get()) == 0;
}

bool MyString::operator!=(const MyString& that) const
{
	return !operator==(that);
}

char& MyString::operator[](int index)
{
	return mBuffer[index];
}

const char& MyString::operator[](int index) const
{
	// TODO: For some reason the const version is not being used in "string3[0] == 'H'", I'm not sure why
	return mBuffer[index];
}