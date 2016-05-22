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
		bool operator>(const MyString& rhs) const;
		bool operator>=(const MyString& rhs) const;
		bool operator<(const MyString& rhs) const;
		bool operator<=(const MyString& rhs) const;
		const char& operator[](unsigned int i) const;
		char& operator[](unsigned int i);
		const char& at(unsigned int i) const;
		char& at(unsigned int i);
		MyString operator+(const MyString& rhs) const;
		void operator=(const MyString& rhs);
		void operator+=(const MyString& rhs);
		bool empty() const;
		size_t size() const;
		const char* c_str() const;
};
