#pragma once
#include <memory>
#include <cstring>

class MyString
{
	// TODO

	public:
		MyString();

		MyString(const char* argString);

		MyString(const MyString& argString);
    
        MyString(MyString&& argString);

		const bool empty() const;

		const size_t size() const;	
		
		const char* c_str() const;	

		const bool operator == (const MyString& argString) const;

		const bool operator != (const MyString& argString) const;
    
        const bool operator < (const MyString& argString) const;

		char& operator[](size_t index) const;
		
		MyString& operator=(const MyString& argString);
    
        //move operator
        MyString& operator=(MyString&& argString);
		
		MyString operator+(const MyString& argString) const;
		
		MyString& operator+=(const MyString& argString);
		
	private:

        std::unique_ptr<char[]> buffer;
};
