#include "string.h"

#include <algorithm>
#include <iterator>
#include <memory>
#include <string>


const char* EMPTY = "";


size_t strlen(const char* s)
{
	size_t len = 0;

	while (s[len] != '\0')
		len++;

	return len;
}


String::String() {}

String::~String() {}

String::String(const String& o)
{
	mSize = o.size();

	mValue = char_ptr(new char[mSize + 1]);

	std::copy_n(o.begin(), mSize, begin());

	mValue[mSize + 1] = '\0';
}

String::String(const char* s)
{
	mSize = strlen(s);

	mValue = char_ptr(new char[mSize + 1]);

	std::copy_n(s, mSize + 1, begin());
}

template<typename It> String::String(It first, It last)
{
	mSize = std::distance(first, last);

	mValue = char_ptr(new char[mSize + 1]);

	std::copy_n(first, mSize, begin());

	mValue[mSize + 1] = '\0';
}

template String::String(std::string::iterator first, std::string::iterator last);

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

std::ostream& operator<<(std::ostream& stream, const String& s)
{
	for(auto c: s) stream << c;
	return stream;
}
