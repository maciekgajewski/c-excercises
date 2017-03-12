
#include "string.h"

#include <iostream>
#include <cstring>
#include <cassert>

int main()
{
	{
		// First check if const char* constructor and c_str() method
		// work as these will be used for tests later on
		String::String s("abc");
		assert(std::strcmp(s.c_str(), "abc") == 0);
		assert(s.length() == 3);
	}

	{
		// Test default constructor
		String::String s;
		assert(std::strcmp(s.c_str(), "") == 0);
		assert(s.length() == 0);
	}

	{
		// Test copy constructor
		const String::String s = "abc";
		String::String copy(s);
		assert(std::strcmp(copy.c_str(), "abc") == 0);
		assert(copy.length() == 3);
	}

	{
		// Test move constructor
		String::String s = "abc";
		String::String move = std::move(s);
		assert(std::strcmp(move.c_str(), "abc") == 0);
		assert(move.length() == 3);
	}

	{
		// Copy assignment
		String::String s = "abc", t, u;
		u = t = s;
		assert(std::strcmp(t.c_str(), "abc") == 0);
		assert(t.length() == 3);
		assert(std::strcmp(u.c_str(), "abc") == 0);
		assert(u.length() == 3);
	}

	{
		// Move assignment
		String::String s = "abc", t, u;
		u = t = std::move(s);
		assert(std::strcmp(t.c_str(), "abc") == 0);
		assert(t.length() == 3);
		assert(std::strcmp(u.c_str(), "abc") == 0);
		assert(u.length() == 3);
	}

	{
		// const char* assignment
		String::String s;
		s = "abc";
		assert(std::strcmp(s.c_str(), "abc") == 0);
		assert(s.length() == 3);
	}

	{
		// operator+
		String::String s, t = "abc", u = "defg";
		s = t + u;
		assert(std::strcmp(s.c_str(), "abcdefg") == 0);
		assert(s.length() == 7);
		assert(std::strcmp(t.c_str(), "abc") == 0);
		assert(t.length() == 3);
		assert(std::strcmp(u.c_str(), "defg") == 0);
		assert(u.length() == 4);
	}

	{
		// operator+=
		String::String s = "abc", t = "defg";
		s += t;
		assert(std::strcmp(s.c_str(), "abcdefg") == 0);
		assert(s.length() == 7);
		assert(std::strcmp(t.c_str(), "defg") == 0);
		assert(t.length() == 4);
	}

	{
		// operator[]
		const char* raw = "abcd";
		String::String s = raw;
		for (size_t i = 0; i < s.length(); i++)
			assert(s[i] == raw[i]);

		for (size_t i = 0; i < s.length(); i++)
		{
			s[i] = '0';
			assert(s[i] == '0');
		}
	}

	{
		// operator[] const
		const char* raw = "abcd";
		const String::String s = raw;
		for (size_t i = 0; i < s.length(); i++)
			assert(s[i] == raw[i]);
	}

	{
		// operator==
		const String::String s = "abc";
		const String::String t = "abc";
		const String::String u = "abd";
		const String::String v = "abcd";
		assert((s == t) == true);
		assert((s == u) == false);
		assert((s == v) == false);
		assert(String::String("") == String::String());
	}

	{
		// operator!=
		const String::String s = "abc";
		const String::String t = "abc";
		const String::String u = "abd";
		const String::String v = "abcd";
		assert((s != t) == false);
		assert((s != u) == true);
		assert((s != v) == true);
	}
}
