
#include "string.h"

#include <cstring>

namespace String {

String::String(const String& copy):
	mSize(copy.mSize),
	mContents(std::make_unique<char[]>(mSize))
{
	for (size_t idx = 0; idx < mSize; idx++)
		mContents[idx] = copy.mContents[idx];
}

String::String(String&& move):
	mSize(move.mSize),
	mContents(std::move(move.mContents))
{
}

String& String::operator=(const String& copy)
{
	mSize = copy.mSize;
	mContents = std::make_unique<char[]>(mSize);
	for (size_t idx = 0; idx < mSize; idx++)
		mContents[idx] = copy.mContents[idx];
	return *this;
}

String& String::operator=(String&& move)
{
	mSize = move.mSize;
	mContents = std::move(move.mContents);
	return *this;
}

String::String(const char* charString)
{
	*this = charString;
}

String& String::operator=(const char* rhs)
{
	mSize = std::strlen(rhs);

	// Increment string size for the terminating character
	mSize++;
	mContents = std::make_unique<char[]>(mSize);

	// Copy the chars over one by one
	for (size_t idx = 0; idx < mSize; idx++)
		mContents[idx] = rhs[idx];
	return *this;
}

String String::operator+(const String& rhs)
{
	String s;
	s.mSize = mSize + rhs.mSize - 1;
	s.mContents = std::make_unique<char[]>(s.mSize);

	for (size_t idx = 0; idx < mSize - 1; idx++)
		s.mContents[idx] = mContents[idx];

	for (size_t idx = 0; idx < rhs.mSize; idx++)
		s.mContents[idx + mSize - 1] = rhs.mContents[idx];

	return s;
}

String& String::operator+=(const String& rhs)
{
	*this = std::move(*this + rhs);
	return *this;
}

char& String::operator[](const size_t idx)
{
	return mContents[idx];
}

const char& String::operator[](const size_t idx) const
{
	return mContents[idx];
}

bool String::operator==(const String& rhs) const
{
	return std::strcmp(c_str(), rhs.c_str()) == 0;
}

}
