#include "my_string.h"

#include <cstring>

namespace Maciek{
	
String::String(const char *inchar)
    :mBuffer(new char[std::strlen(inchar)+1])
{
	std::strcpy(mBuffer.get(), inchar);
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

    
}