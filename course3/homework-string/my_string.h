#pragma once
#include "my_unique_ptr.h"
#include <memory>

class MyString
{
	private:
		//std::unique_ptr<char[]> buf;
		MyUniquePtr<char[]> buf;

	public:
		MyString() = default;
		MyString(const char* str);
		MyString(const MyString& obj);
		MyString(MyString&& obj);
		~MyString();
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
		MyString& operator=(const MyString& rhs);
		MyString& operator=(MyString&& rhs);
		MyString& operator+=(const MyString& rhs);
		bool empty() const;
		size_t size() const;
		const char* c_str() const;
		const char* begin() const;
		const char* end() const;
};

/*
 * Don't understand why I need to wrap this with namespace std :(
 * If I don't I get the following compilation error:
 * /home/wshayes/projects/cpp_course/c-excercises/course3/homework-string/my_string.h:46:9: error: ‘hash’ is not a class template
 */
namespace std {
	template<>
	struct hash<MyString>
	{
		std::size_t operator()(const MyString& ms) const;
	};
}
