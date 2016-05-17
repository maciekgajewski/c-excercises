#pragma once

#include <memory>


class MyString
{

public:
	MyString() = default;
	MyString(const char* str);
	MyString(const MyString& str);

	bool empty() const;
	std::size_t size() const;
	const char* c_str() const;
		
	MyString& operator=(const char* str);
	MyString& operator=(const MyString& str);
	bool operator==(const MyString& str) const;
	bool operator!=(const MyString& str) const;
	const char& operator[](int idx) const;
	char& operator[](int idx);
	MyString operator+(const MyString& str) const;
	MyString& operator+=(const MyString& str);

private:
	std::unique_ptr<char[]> mBuffer;

};
