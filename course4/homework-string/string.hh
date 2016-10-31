#pragma once

#include <cstring>
#include <memory>
#include <iostream>

namespace course {

class string
{
public:
	string() {}
	string(const char* init_str)
	{
		if (std::strcmp(init_str, "") != 0)
		{
			my_ptr = std::make_unique<char[]>(std::strlen(init_str)+1);
			std::strcpy(my_ptr.get(), init_str);
		}
	}
	string(const string& other_string) 
	{
		if (!other_string.empty())
		{
			my_ptr = std::make_unique<char[]>(other_string.size()+1);
			std::strcpy(my_ptr.get(), other_string.my_ptr.get());
		}
	}

	string(char init_char)
	{
		if (init_char != '\0')
		{
			my_ptr = std::make_unique<char[]>(2);
			my_ptr.get()[0] = init_char;
			my_ptr.get()[1] = '\0';
		}
	}

	bool empty() const
	{
		return !my_ptr;
	}

	int size() const
	{
		return empty() ? 0 : std::strlen(my_ptr.get());;
	}

	int length() const
	{
		return size();
	}

	void clear()
	{
		my_ptr.reset();
	}

	bool operator==(const string& other_string) const
	{
		if (empty() || other_string.empty())
			return empty() && other_string.empty();
		else
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
		if (empty())
			return string(other_string);
		else if (other_string.empty())
			return string(*this);
		else
			return string(my_ptr.get(), other_string.my_ptr.get());
	}

	string& operator+=(const string& other_string)
	{
		if (!other_string.empty())
		{
			std::unique_ptr<char[]> new_ptr = std::make_unique<char[]>(size()+other_string.size()+1);
			if (!empty())
			{
				std::strcpy(new_ptr.get(), my_ptr.get());
				std::strcat(new_ptr.get(), other_string.my_ptr.get());
			}
			else
			{
				std::strcpy(new_ptr.get(), other_string.my_ptr.get());
			}
			my_ptr = std::move(new_ptr);
		}
		return *this;
	}

	const char* c_str() const
	{
		if (empty())
			return "";
		else
			return my_ptr.get();
	}

	string& operator=(const string& other_string)
	{
		if (this != &other_string)
		{
			if (other_string.empty())
			{
				my_ptr.reset();
			}
			else
			{
				my_ptr = std::make_unique<char[]>(other_string.size()+1);
				std::strcpy(my_ptr.get(), other_string.my_ptr.get());
			}
		}
		return *this;
	}

	const char* begin() const
	{
		return my_ptr.get();
	}

	const char* end() const
	{
		return my_ptr.get() + size();
	}

	char* begin()
	{
		return my_ptr.get();
	}

	char* end()
	{
		return begin() + size();
	}

private:
	std::unique_ptr<char[]> my_ptr;

	string(const char* init_str1, const char* init_str2) : my_ptr(std::make_unique<char[]>(std::strlen(init_str1)+std::strlen(init_str2)+1))
	{
		std::strcpy(my_ptr.get(), init_str1);
		std::strcat(my_ptr.get(), init_str2);
	}
};

std::ostream& operator<<(std::ostream& s, const string& strng);
}