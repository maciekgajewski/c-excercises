#include "string.h"

#include <algorithm>
#include <iterator>
#include <memory>

const char* EMPTY = "";

String::String() {}

String::~String() {}

String::String(const String& o)
{
	mSize = o.size();

	mValue = std::unique_ptr<value_type[]>(new char[mSize + 1]);

	std::copy_n(o.begin(), mSize, begin());

	mValue[mSize + 1] = '\0';
}

String::String(const char* s)
{
	mSize = 0;

	while (s[mSize] != '\0')
		mSize++;

	mValue = std::unique_ptr<value_type[]>(new char[mSize + 1]);

	std::copy_n(s, mSize + 1, mValue.get());
}

template<typename It> String::String(It first, It last)
{
	mSize = std::distance(first, last);

	mValue = new char[mSize + 1]; // Why does direct assignment works here but not in constructors?

	std::copy_n(first, mSize, mValue);

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

String::const_iterator String::begin() const
{
	return mValue.get();
}

String::const_iterator String::end() const
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

bool String::operator==(const String& s) const
{
	return std::equal(begin(), end(), s.begin());
}

bool String::operator==(const char* s) const
{
	if (empty() and s == '\0') return true;

	return std::equal(mValue.get(), mValue.get() + mSize, s);
}
