#include "string.h"

#include <algorithm>
#include <iterator>
#include <memory>
#include <string>
#include <cstring>


const char* EMPTY = "";


String::String() = default;

String::~String() = default;

String::String(const String& o): String(o.begin(), o.end()) {}

String::String(const char* s): String(s, s + std::strlen(s)) {}

template String::String(std::string::iterator first, std::string::iterator last);

template<typename It> String::String(It first, It last)
{
	mSize = std::distance(first, last);

	mValue.reset(new char[mSize + 1]);

	std::copy_n(first, mSize, begin());

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
	if (empty()) return *s == '\0';

	return std::equal(begin(), end(), s);
}

std::ostream& operator<<(std::ostream& stream, const String& s)
{
	return stream << s.c_str();
}
