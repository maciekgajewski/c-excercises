#pragma once 

#include <iostream>
#include <memory>

// ARS -- week 06. 20170307

namespace mystring
{

class iterator;

class MyString
{
private:
	std::unique_ptr<char[]> mStr;
	void Reset_mStr(int new_size, const char* str);

public:
// DO not define default constructor, but rely on default generated constructor where mStr will be assigned nullptr
	MyString() = default ; // default constructor

	MyString(const char* str); // User defined constructor

	MyString(const MyString& str);  // copy constructor
	MyString& operator = (const MyString& str);  // copy assignment
	MyString& operator = (const char* str); // assignment using char*

	MyString(MyString&& str);  // move constructor
	MyString& operator = (MyString&& str);  // move assignment
	
	char& operator[] (const size_t index); 
	const char& operator[] (const size_t index) const; 

	MyString  operator+ (const MyString& str); // concatenation
	MyString&  operator+= (const MyString& str); // concatenation assignment

	bool  operator== (const MyString& str); 
	bool  operator!= (const MyString& str);
	bool  operator== (const char* str); 
	bool  operator!= (const char* str);

	unsigned int length() const;
	const char* c_str() const; 

	const mystring::iterator begin();
	const mystring::iterator end();

};


/* ARS 20170410. Probably need some const iterator class as well and some more operaors on the iterator, like postfix increments. 
*/

class iterator
{
public:
	iterator(const MyString& str, int pos) ;
	iterator operator++();
	char operator*();
	bool operator!=(const iterator& rhs);
	bool operator==(const iterator& rhs);
private:
	MyString m_str;
	char m_pos;
};

inline std::ostream& operator<<(std::ostream& stream, const MyString& str)
{
	stream << str.c_str();
	return stream;
}

}; // namespace
