#include "Stream.h"
#include <cstdio>
#include <string>
#include <stdexcept>

Stream::Stream(const char* file)
{
	if ((m_fileptr = std::fopen(file, "w")) == nullptr)
	{
		throw (std::runtime_error("Cannot open file\n")); 
	}
}

Stream::Stream(FILE* stream)
{
	m_fileptr = stream;
}

Stream::~Stream()
{
	if (m_fileptr)
	{
		std::fclose(m_fileptr);
	}
}

Stream& Stream::operator << (int x)
{
	std::fprintf(m_fileptr, "%d",x );
	return *this; 
}

Stream& Stream::operator << (long l)
{
	std::fprintf(m_fileptr, "%ld", l);
	return *this; 
}

Stream& Stream::operator << (const char* s)
{
	std::fprintf(m_fileptr, "%s", s);
	return *this; 
}

Stream& Stream::operator << (std::string s)
{
	std::fprintf(m_fileptr, "%s", s.c_str());
	if (s == Endl)
		std::fflush(m_fileptr);
	return *this; 
}

Stream& Stream::operator << (bool b)
{
	if (b)
		std::fprintf(m_fileptr,"true");
	else
		std::fprintf(m_fileptr, "false");
	return *this; 
}

Stream& Stream::operator << (char c)
{
	std::fprintf(m_fileptr, "%c", c);
	return *this; 
}

Stream& Stream::operator << (float f)
{
	std::fprintf(m_fileptr, "%f", f);
	return *this; 
}

Stream& Stream::operator << (double d)
{
	std::fprintf(m_fileptr, "%lf", d);
	return *this; 
}

