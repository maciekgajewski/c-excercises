#pragma once

#include <memory>
#include <cstring>

class MyString
{
public:
	MyString() : MyString("") {}
	MyString(const char* init_str) : str_len(std::strlen(init_str)), my_ptr(new char[str_len+1])
	{
		std::strcpy(my_ptr.get(), init_str);
	}
	MyString(const MyString& other_string) : str_len(other_string.size()), my_ptr(new char[str_len+1])
	{
		std::strcpy(my_ptr.get(), other_string.my_ptr.get());
	}
	MyString(const char* init_str1, const char* init_str2) : str_len(std::strlen(init_str1)+std::strlen(init_str2)), my_ptr(new char[str_len+1])
	{
		std::strcpy(my_ptr.get(), init_str1);
		std::strcat(my_ptr.get(), init_str2);
	}
	
	bool empty() const
	{
		return str_len == 0;
	}

	int size() const
	{
		return str_len;
	}

	bool operator==(const MyString& other_string) const
	{
		return std::strcmp(my_ptr.get(), other_string.my_ptr.get()) == 0;
	}
	
	char operator[](std::size_t idx) const
	{
		return my_ptr[idx];
	}

	char& operator[](std::size_t idx)
	{
		return my_ptr[idx];
	}

	bool operator!=(const MyString& other_string) const
	{
		return !(*this == other_string);
	}
	
	MyString operator+(const MyString& other_string) const
	{
		return MyString(my_ptr.get(), other_string.my_ptr.get());
	}
	
	MyString& operator+=(const MyString & other_string)
	{
		if (!other_string.empty())
		{
			str_len += other_string.size();
			char* new_ptr = new char[str_len+1];
			std::strcpy(new_ptr, my_ptr.get());
			std::strcat(new_ptr, other_string.my_ptr.get());
			my_ptr.reset(new_ptr);
		}
		return *this;
	}
	
	char* c_str() const
	{
		return my_ptr.get();
	}

	MyString& operator=(const MyString& other_string)
	{
		if (this != &other_string) 
		{ 
			str_len = other_string.str_len;
			my_ptr.reset(new char[str_len+1]);
			std::strcpy(my_ptr.get(), other_string.my_ptr.get());
		}
		return *this;
	}
	
	bool operator<(const MyString& other_string)
	{
		return std::strcmp(my_ptr.get(), other_string.my_ptr.get()) < 0;
	}

	
private:
	int str_len;
	std::unique_ptr<char[]> my_ptr;
};
