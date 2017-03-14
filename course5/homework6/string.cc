#include <memory>
#include <cstring>

#include "string.h"


#include <iostream>
namespace jds {

String::String()
{
	mLength = 0;
}

String::String(String const & that)
{
	mLength = that.mLength;
	mBuffer = std::make_unique<char[]>(mLength + 1);
	std::memcpy(this->mBuffer.get(), that.mBuffer.get(), that.mLength);
	mBuffer.get()[mLength] = '\0';
}

String::String(String && that)
{
	mBuffer = std::unique_ptr<char []>(that.mBuffer.release());
	mLength = that.mLength;
	that.mLength = 0;
}

String::String(char const * source)
{
	mLength = strlen(source);
	mBuffer = std::make_unique<char[]>(mLength + 1);
	std::memcpy(mBuffer.get(), source, mLength);
	mBuffer.get()[mLength] = '\0';
}

void String::operator=(String const & that)
{
	mLength = that.mLength;
	mBuffer = std::make_unique<char[]>(mLength + 1);
	std::memcpy(mBuffer.get(), that.mBuffer.get(), mLength);
	mBuffer.get()[mLength] = '\0';
}

void String::operator=(String && that)
{
	mBuffer = std::unique_ptr<char []>(that.mBuffer.release());
	mLength = that.mLength;
	that.mLength = 0;
}

void String::operator=(char const * source)
{
	mLength = strlen(source);
	mBuffer = std::make_unique<char[]>(mLength + 1);
	std::memcpy(mBuffer.get(), source, mLength);
	mBuffer.get()[mLength] = '\0';
}

unsigned String::length() const
{
	return mLength;
}

char& String::operator[](unsigned index)
{
	if (index >= mLength)
	{
		throw std::runtime_error("String index out of bounds");
	}
	return mBuffer.get()[index];
}

char String::operator[](unsigned index) const
{
	if (index >= mLength)
	{
		throw std::runtime_error("String index out of bounds");
	}
	return mBuffer.get()[index];
}

String String::operator+(String const & that) const
{
	String result = *this;
	result += that;
	return result;
}

String& String::operator+=(String const & that)
{
	std::unique_ptr<char[]> newBuffer = std::make_unique<char[]>(mLength + that.mLength + 1);
	std::memcpy(newBuffer.get(), mBuffer.get(), mLength);
	std::memcpy(newBuffer.get() + mLength, that.mBuffer.get(), that.mLength);
	mLength += that.mLength;
	newBuffer.get()[mLength] = '\0';
	mBuffer = std::unique_ptr<char []>(newBuffer.release());
	return *this;
}

char const * String::c_str() const
{
	if (mLength) {
		return mBuffer.get();
	} else {
		return "";
	}
}

}

std::ostream& operator<<(std::ostream& s, jds::String const & value)
{
	s << value.c_str();
	return s;
}
