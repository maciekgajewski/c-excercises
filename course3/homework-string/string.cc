#include "string.h"

#include <cstring>
#include <boost/functional/hash.hpp>


Karun::String::String(const char* str)
{
	if (str[0] != '\0')
	{
		mBuffer.reset(new char[std::strlen(str) + 1]);
		std::strcpy(mBuffer.get(), str);
	}
}

Karun::String::String(const Karun::String& str)
{
	if (!str.empty())
	{
		mBuffer.reset(new char[str.size() + 1]);
		std::strcpy(mBuffer.get(), str.mBuffer.get());
	}
}

Karun::String::String(Karun::String&& str)
{
	if (!str.empty())
	{
		mBuffer.swap(str.mBuffer);
	}
}

bool Karun::String::empty() const
{
	return !mBuffer;
}

std::size_t Karun::String::size() const
{
	return empty() ? 0 : std::strlen(mBuffer.get());
}

const char* Karun::String::c_str() const
{
	return empty() ? "" : mBuffer.get();
}

int Karun::String::compare(const Karun::String& str) const
{
	return std::strcmp(c_str(), str.c_str());
}

Karun::String::iterator Karun::String::begin()
{
	return mBuffer.get();
}

Karun::String::const_iterator Karun::String::begin() const
{
	return mBuffer.get();
}

Karun::String::iterator Karun::String::end()
{
	return mBuffer.get() + size();
}

Karun::String::const_iterator Karun::String::end() const
{
	return mBuffer.get() + size();
}

Karun::String& Karun::String::operator=(const Karun::String& str)
{
	if (str.empty())
	{
		mBuffer.reset();
	}
	else
	{
		mBuffer.reset(new char[str.size() + 1]);
		std::strcpy(mBuffer.get(), str.mBuffer.get());
	}

	return *this;
}

Karun::String& Karun::String::operator=(Karun::String&& str)
{
	if (str.empty())
	{
		mBuffer.reset();
	}
	else
	{
		mBuffer.swap(str.mBuffer);
	}

	return *this;
}

bool Karun::String::operator==(const Karun::String& str) const
{
	if (empty() && str.empty()) return true;
	if (empty() || str.empty()) return false;

	return std::strcmp(mBuffer.get(), str.mBuffer.get()) == 0;
}

bool Karun::String::operator!=(const Karun::String& str) const
{
	return !operator==(str);
}

bool Karun::String::operator<(const Karun::String& str) const
{
	return compare(str) < 0;
}

const char& Karun::String::operator[](int idx) const
{
	return mBuffer.get()[idx];
}

char& Karun::String::operator[](int idx)
{
	return mBuffer.get()[idx];
}

Karun::String Karun::String::operator+(const Karun::String& str) const
{
	if (empty()) return str;
	else if (str.empty()) return *this;
	
	Karun::String retStr;
	retStr.mBuffer.reset(new char[size() + str.size() + 1]);
	std::strcpy(retStr.mBuffer.get(), mBuffer.get());
	std::strcpy(retStr.mBuffer.get() + size(), str.mBuffer.get());
	return retStr;
}

Karun::String& Karun::String::operator+=(const Karun::String& str)
{
	*this = *this + str;
	return *this;
}

std::size_t std::hash<Karun::String>::operator()(const Karun::String& str) const
{
	std::size_t seed = 0;
	for (auto& c : str)
		boost::hash_combine(seed, c);
	return seed;
}
