
#include "string.h"

namespace String {

String::String(const String& copy):
	mContents(std::make_unique<char[]>(mSize)),
	mSize(copy.mSize)
{
	for (unsigned idx = 0; idx < mSize; idx++)
		mContents[idx] = copy.mContents[idx];
}

String::String(String&& move):
	mContents(std::move(move.mContents)),
	mSize(move.mSize)
{
}

String& String::operator=(const String& copy)
{
	mSize = copy.mSize;
	mContents = std::make_unique<char[]>(mSize);
	for (unsigned idx = 0; idx < mSize; idx++)
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

String& String::operator=(const char* lhs)
{
	// Find the end of the string
	while (lhs[mSize] != '\0')
		mSize++;

	// Increment string size for the terminating character
	mSize++;
	mContents = std::make_unique<char[]>(mSize);

	// Copy the chars over one by one
	for (unsigned idx = 0; idx < mSize; idx++)
		mContents[idx] = lhs[idx];
	return *this;
}

String String::operator+(const String& lhs)
{
	String s;
	s.mSize = mSize + lhs.mSize - 1;
	s.mContents = std::make_unique<char[]>(s.mSize);

	for (unsigned idx = 0; idx < mSize - 1; idx++)
		s.mContents[idx] = mContents[idx];

	for (unsigned idx = 0; idx < lhs.mSize; idx++)
		s.mContents[idx + mSize - 1] = lhs.mContents[idx];

	return s;
}

String& String::operator+=(const String& lhs)
{
	*this = std::move(*this + lhs);
	return *this;
}

char& String::operator[](const int idx)
{
	if (static_cast<unsigned>(idx) >= mSize)
		throw std::out_of_range("string index out of range");
	return mContents[idx];;
}

const char& String::operator[](const int idx) const
{
	if (static_cast<unsigned>(idx) >= mSize)
		throw std::out_of_range("string index out of range");
	return mContents[idx];;
}

bool String::operator==(const String& lhs) const
{
	if (mSize != lhs.mSize)
		return false;

	for (size_t idx = 0; idx < mSize - 1; idx++)
	{
		if (mContents[idx] != lhs.mContents[idx])
			return false;
	}

	return true;
}

}
