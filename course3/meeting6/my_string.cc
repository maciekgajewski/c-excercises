#include "my_string.h"

#include <cstring>
#include <iostream>

namespace Maciek{

String::String()
{
	std::cout << "default, this=" << this << std::endl;
}

	
String::String(const char *inchar)
    :mBuffer(new char[std::strlen(inchar) + 1])
{
	std::strcpy(mBuffer.get(), inchar);
	
	std::cout << "from cstr, this=" << this << std::endl;
}

String::String(const String& str)
{
    std::cout << "copy, this=" << this << std::endl;
	if (!str.empty())
	{
		mBuffer.reset(new char[str.size() + 1]);
		std::strcpy(mBuffer.get(), str.mBuffer.get());
	}
}

String::~String()
{
	std::cout << "destroyed, this=" << this << std::endl;
}

std::size_t String::size() const
{
	if(!mBuffer)
		return 0;
    
	return std::strlen(mBuffer.get());
}

bool String::empty() const
{
	if(!mBuffer)
		return true;
	
	return mBuffer[0] == '\0'; 
}

bool String::operator==(const String& other) const
{
	if (this->empty() && other.empty()) return true;
	if (this->empty() != other.empty()) return false;
	return std::strcmp(this->mBuffer.get(), other.mBuffer.get()) == 0;
}

const char* String::c_str() const
{
	if (mBuffer)
		return mBuffer.get();
	else
		return "";
}

String String::operator+(const String& other) const
{
	String res(*this);
	res += other;
	return res;
}

String& String::operator+=(const String& other)
{
	std::cout << "oper+=, this=" << this << std::endl;
	if (!other.empty())
	{
		auto currentSize = size();
		auto newBuffer = std::make_unique<char[]>(currentSize + other.size() + 1);
		std::strcpy(newBuffer.get(), mBuffer.get());
		std::strcpy(newBuffer.get() + currentSize, other.c_str());
		
		mBuffer.swap(newBuffer);
	}
	return *this;
}

String& String::operator=(const String& other)
{
	std::cout << "oper=, this=" << this << std::endl;
	if (other.empty())
	{
		mBuffer.reset();
	}
	else
	{
		mBuffer = std::make_unique<char[]>(other.size() + 1);
		std::strcpy(mBuffer.get(), other.c_str());
	}
	return *this;
}

}