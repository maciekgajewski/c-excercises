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

	char& operator[](const int idx);
	const char& operator[](const int idx) const;

	bool operator==(const String&) const;
	bool operator!=(const String& lhs) const { return !(*this == lhs); }

	const char* c_str() const { return mSize > 0 ? mContents.get() : ""; }
	size_t length() const { return mSize > 0 ? mSize - 1 : 0; }

private:
	std::unique_ptr<char[]> mContents;
	size_t mSize = 0;
};

inline std::ostream& operator<<(std::ostream& s, const String& str)
{
	s << str.c_str();
	return s;
}

}
