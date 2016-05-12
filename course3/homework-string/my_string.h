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

	bool operator==(const MyString& str) const;
	bool operator!=(const MyString& str) const;
	const char& operator[](int idx) const;
	char& operator[](int idx);

private:
	std::unique_ptr<char[]> mBuffer;

};
