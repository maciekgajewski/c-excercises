#pragma once

#include <memory>

namespace jds {

class String
{
public:
	using iterator = char *;
	using const_iterator = char const *;

	String() = default;
	String(String const & that);
	String(String && that);
	String(char const * source);
	void operator=(String const & that);
	void operator=(String && that);
	void operator=(char const * source);
	unsigned length() const;
	char& operator[](unsigned index);
	char operator[](unsigned index) const;
	String operator+(String const & that) const;
	String& operator+=(String const & that);
	bool operator==(String const & that) const;
	bool operator==(char const * that) const;
	bool operator!=(String const & that) const;
	bool operator!=(char const * that) const;
	char const * c_str() const;
	String::iterator begin();
	String::const_iterator begin() const;
	String::iterator end();
	String::const_iterator end() const;

private:
	std::unique_ptr<char[]> mBuffer = nullptr;
	unsigned mLength = 0;
};

std::ostream& operator<<(std::ostream& s, jds::String const & value);
bool operator==(char const * left, String const & right);
bool operator!=(char const * left, String const & right);

}
