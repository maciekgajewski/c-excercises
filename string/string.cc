#include "string.h"

#include <algorithm>
#include <iterator>
#include <memory>

const char* EMPTY = "";

String::String() {}

String::~String() {}

String::String(const char* s)
{
	mSize = 0;

	while (s[mSize] != '\0')
		mSize++;

	mValue = std::unique_ptr<char[]>(new char[mSize + 1]);

	for (std::size_t i = 0; i <= mSize; i++)
		mValue[i] = s[i];
}

template<typename It> String::String(It first, It last)
{
	mSize = std::distance(first, last);

	mValue = std::unique_ptr<char[]>(new char[mSize + 1]);

	for (std::size_t i = 0; i < mSize; i++) {
		mValue[i] = *first;
		first++;
	}

	mValue[mSize + 1] = '\0';
}

String::iterator String::begin()
{
	return mValue.get();
}

String::iterator String::end()
{
	return mValue.get() + mSize;
}

std::size_t String::size() const
{
	return mSize;
}

bool String::empty() const
{
	return mSize == 0;
}

const char* String::c_str() const
{
	if (empty()) return EMPTY;

	return mValue.get();
}

bool String::operator==(const char* s) const
{
	return std::equal(mValue.get(), mValue.get() + mSize, s);
}
