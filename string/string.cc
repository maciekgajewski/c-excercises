#include "string.h"

#include <algorithm>
#include <iterator>


String::String()
{
	_value = new char('\0');
	_size = 0;
}

String::~String()
{
	delete [] _value;
}

String::String(const char* s)
{
	_size = 0;

	while (s[_size] != '\0')
		_size++;

	_value = new char(_size + 1);

	for (std::size_t i = 0; i <= _size; i++)
		_value[i] = s[i];
}

template<typename It> String::String(It first, It last)
{
	_size = std::distance(first, last);
	_value = new char[_size];

	for (std::size_t i = 0; i < _size; i++) {
		_value[i] = *first;
		first++;
	}
}

String::iterator String::begin()
{
	return _value;
}

String::iterator String::end()
{
	return _value + _size;
}

std::size_t String::size() const
{
	return _size;
}

bool String::empty() const
{
	return _size == 0;
}

const char* String::c_str() const
{
	return _value;
}

bool String::operator==(const char* s) const {
	return std::equal(_value, _value + _size, s);
}
