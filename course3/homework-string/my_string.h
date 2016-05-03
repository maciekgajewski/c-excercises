#pragma once
#include <vector>
#include <iostream>
#include <cstring>

class MyString
{
public:
	MyString()	
	{ 
		//std::cout << "Default constructor";
	}

	MyString(MyString& other)
	{
		this->innerStorage = other.innerStorage;
	}

	MyString(const char* initialValue)
	{
		innerStorage.insert(
			innerStorage.begin(),
			initialValue,
			initialValue + strlen(initialValue));
	}

	bool empty() const
	{
		return this->size() == 0;
	}

	int size() const
	{
		return innerStorage.size();
	}

	bool operator==(const MyString& other)
	{
    	return this->innerStorage == other.innerStorage;
	}

	bool operator!=(const MyString& other)
	{
		return !(*this == other);
	}

	char& operator[](int index)
	{
		return innerStorage[index];
	}

private:
	std::vector<char> innerStorage; 
};
