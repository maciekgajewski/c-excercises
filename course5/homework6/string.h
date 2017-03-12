#pragma once

#include <memory>
#include <ostream>

namespace String {

class String
{
public:
	String() = default;
	~String() = default;
	String(const String&);
	String(String&&);
	String& operator=(const String&);
	String& operator=(String&&);

	String(const char*);
	String& operator=(const char*);

	String operator+(const String&);
	String& operator+=(const String&);

	char& operator[](const size_t idx);
	const char& operator[](const size_t idx) const;

	bool operator==(const String&) const;
	bool operator!=(const String& rhs) const { return !(*this == rhs); }

	const char* c_str() const { return mSize > 0 ? mContents.get() : ""; }
	size_t length() const { return mSize > 0 ? mSize - 1 : 0; }

private:
	size_t mSize = 0;
	std::unique_ptr<char[]> mContents;
};

inline std::ostream& operator<<(std::ostream& s, const String& str)
{
	s << str.c_str();
	return s;
}

}
