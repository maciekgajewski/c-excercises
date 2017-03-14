#ifndef _JDS_STRING_H_
#define _JDS_STRING_H_

#include <memory>

namespace jds {

class String
{
public:
	String();
	String(String const & that);
	String(String && that);
	String(char const * source);
	void operator=(String const & that);
	void operator=(String && that);
	void operator=(char const * source);
	unsigned length() const;
	char& operator[](unsigned index);
	char operator[](unsigned index) const;
	String operator+(String const & that) const;
	String& operator+=(String const & that);
	char const * c_str() const;

private:
	std::unique_ptr<char[]> mBuffer;
	unsigned mLength;
};

}

std::ostream& operator<<(std::ostream& s, jds::String const & value);

#endif
