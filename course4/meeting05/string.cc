#include "string.hh"

#include <cstring>
#include <cassert>

namespace maciek {
	

string::string(const char* s)
{
	assert(s);
	
	mLength = std::strlen(s);
	mData = std::make_unique<char[]>(mLength);
	std::copy(s, s + mLength, mData.get());
}
	
}