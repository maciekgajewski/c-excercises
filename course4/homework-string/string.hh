#pragma once

#include <iostream>
#include <memory>

namespace course {

class string
{
public:
	string(): mSize(0) {}
	string(const char* other);
	string(const string& other);
	string(string&& other);

	bool empty() const;
	std::size_t size() const;
	std::size_t length() const;
	const char* c_str() const;

	void clear();

	string& operator=(const string& other);
	bool operator==(const string& other) const;
	bool operator!=(const string& other) const;
	bool operator<(const string& other) const;

	char operator[](int i) const;
	char& operator[](int i);

	string operator+(const string& other) const;
	string& operator+=(const string& other);

private:
	std::size_t mSize;
	std::unique_ptr<char[]> mBuffer;
};

std::ostream& operator<<(std::ostream& out, const string& str);

}
