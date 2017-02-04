#include "my_string.h"

#include <cstring>

namespace Maciek{
	
String::String(const char *inchar)
    :mBuffer(new char[std::strlen(inchar) + 1])
{
	std::strcpy(mBuffer.get(), inchar);
}

String::String(const String& str)
{
	if (!str.empty())
	{
		mBuffer.reset(new char[str.size() + 1]);
		std::strcpy(mBuffer.get(), str.mBuffer.get());
	}
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

bool String::operator==(const String& other)
{
	if (this->empty() && other.empty()) return true;
	if (this->empty() != other.empty()) return false;
	return std::strcmp(this->mBuffer.get(), other.mBuffer.get()) == 0;
}

    
}