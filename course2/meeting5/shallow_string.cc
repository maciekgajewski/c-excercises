#include <cassert>
#include <iostream>
#include <cstring>


class ShallowString
{
public:

	ShallowString()
	{
		mStr = "";
	}

	ShallowString(const char* str)
	{
		mStr = str;
	}

	ShallowString(const ShallowString& other)
	{
		mStr = other.mStr;
	}

	friend std::ostream& operator<<(std::ostream& o, const ShallowString& s)
	{
		return o << s.mStr;
	}

	const char& operator[](int i) const { return mStr[i]; }

	char& operator[](int i) { return const_cast<char&>(mStr[i]); }

private:

	const char* mStr;
};

int main()
{
	//char buffer[] = "abcdefg";

	ShallowString s1("12345");

	
	assert(s1[0] == 'a');
	assert(s1[1] == 'b');
	assert(s1[2] == 'c');

	ShallowString s2 = s1;

	//s1[0] = 'x';

	std::cout << "s1=" << s1 << std::endl;
	std::cout << "s2=" << s2 << std::endl;
}
