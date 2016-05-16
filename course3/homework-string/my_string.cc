#include "stdafx.h"
#include "my_string.h"

#include <cstring>

namespace Maciek {

	String::String(): mBuffer(nullptr), mSize(0) { }

	String::String(const char *inchar)
		:mSize(std::strlen(inchar)), 
		mBuffer(new char[mSize + 1])
	{
		std::strcpy(mBuffer.get(), inchar);
	}

	String::String(const String& str)
	{
		if (!str.empty())
		{
			mSize = str.mSize;
			mBuffer.reset(new char[mSize + 1]);
			std::strcpy(mBuffer.get(), str.mBuffer.get());
		}
	}

	std::size_t String::size() const
	{
		return mSize;
	}

	bool String::empty() const
	{
		return !mBuffer || mSize == 0;
	}

	bool String::operator==(const String& other)
	{
		if (this->empty() && other.empty()) return true;
		if (this->empty() != other.empty()) return false;
		return std::strcmp(this->mBuffer.get(), other.mBuffer.get()) == 0;
	}

	bool String::operator!=(const String& other)
	{
		return !(*this == other);
	}

	char& String::operator[](const int i) const
	{
		if (i > mSize)
		{
			throw new std::exception();
		}
		return mBuffer[i];
	}

}