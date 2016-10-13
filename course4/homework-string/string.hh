#pragma once

#include <cstring>
#include <memory>

namespace course {

class string
{
public:
	string() : string("") {}
	string(const char* init_str) : my_ptr(new char[std::strlen(init_str)+1])
	{
		std::strcpy(my_ptr.get(), init_str);
	}
	string(const string& other_string) : my_ptr(new char[other_string.size()+1])
	{
		std::strcpy(my_ptr.get(), other_string.my_ptr.get());
	}
	string(const char* init_str1, const char* init_str2) : my_ptr(new char[std::strlen(init_str1)+std::strlen(init_str2)+1])
	{
		std::strcpy(my_ptr.get(), init_str1);
		std::strcat(my_ptr.get(), init_str2);
	}

	bool empty() const
	{
		return size()==0;
	}

	int size() const
	{
		return std::strlen(my_ptr.get());
	}

	int length() const
	{
		return size();
	}

	void clear()
	{
		char* new_ptr = new char[1];
		std::strcpy(new_ptr, "");
		my_ptr.reset(new_ptr);
	}

	bool operator==(const string& other_string) const
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

	bool operator!=(const string& other_string) const
	{
		return !(*this == other_string);
	}

	string operator+(const string& other_string) const
	{
		return string(my_ptr.get(), other_string.my_ptr.get());
	}

	string& operator+=(const string & other_string)
	{
		if (!other_string.empty())
		{
			char* new_ptr = new char[size()+other_string.size()+1];
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

	string& operator=(const string& other_string)
	{
		if (this != &other_string)
		{
			my_ptr.reset(new char[other_string.size()+1]);
			std::strcpy(my_ptr.get(), other_string.my_ptr.get());
		}
		return *this;
	}

	bool operator<(const string& other_string)
	{
		return std::strcmp(my_ptr.get(), other_string.my_ptr.get()) < 0;
	}

private:
	std::unique_ptr<char[]> my_ptr;
};

std::ostream& operator<<(std::ostream& s, const string& strng);
}