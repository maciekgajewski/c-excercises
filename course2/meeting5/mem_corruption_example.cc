#include <memory>
#include <iostream>
#include <cstring>
#include <cassert>

class ZachsString
{
public:
	ZachsString(const char* str)
	{
		mLength = std::strlen(str);
		mData = std::unique_ptr<char[]>(new char[mLength]);
		std::strcpy(data(), str);
	}
	
	char* data() const { return mData.get(); }

	bool operator==(const char* other)
	{
	//	return std::strcmp(data(), other) == 0;
		int i = 0;
		for (; i < mLength; i++)
			if (mData[i] != other[i])
				return false;

		if (other[i] != '\0')
			return false;

		return true;
	}
	
	friend std::ostream& operator<<(std::ostream& os, ZachsString& string)
 	{
		os << string.data();
		return os;
	}

	char& operator[](int i) { return data()[i]; }
private:
	int mLength;
	std::unique_ptr<char[]> mData;
};

int main()
{
	ZachsString s("abc");

	std::cout << "string=" << s << std::endl;

	assert(s[0] == 'a');
	assert(s[1] == 'b');
	assert(s[2] == 'c');
	assert(s == "abc");

	s[0] = 'x';
	s[1] = 'y';
	s[2] = 'z';

	assert(s == "xyz");
}
