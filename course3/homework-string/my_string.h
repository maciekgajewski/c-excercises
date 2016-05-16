#pragma once
#include <memory>

class MyString
{
	private:
		std::unique_ptr<char[]> buf;

	public:
		MyString() = default;
		MyString(const char* str);
		MyString(const MyString& obj);
		bool operator==(const MyString& rhs) const;
		bool operator!=(const MyString& rhs) const;
		const char& operator[](int i) const;
		char& operator[](int i);
		MyString operator+(const MyString& rhs) const;
		void operator=(const MyString& rhs);
		bool empty() const;
		size_t size() const;
};
