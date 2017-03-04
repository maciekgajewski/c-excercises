#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <stdexcept>
#include <string>

/***
Define a “Stream” class, that allows for easy printing of values to a file
- Let the class manage the file: ie open the file in constructor and close it in destructor.
- Overload operator<< for the class, so that it can be used to print some types.
- Define a global variable of the “Stream” type, call it, say, “Cout”, that will write to stdout.
***/

class Stream
{
public:
	// Constructors
	Stream() // default
	{
		throw std::runtime_error("Stream must be constructed with a filename: Stream('filename.txt')");
	}
	Stream(const Stream&) = delete; // copy

	Stream(Stream&& src) // move
	{
		fname = src.fname;
		fp = src.fp;
	}
	Stream(const char* fname)
	{
		this->fname = fname;
		this->fp = std::fopen(fname, "a");
	}
	Stream(std::FILE *)
	{
		this->fp = stdout;
	}

	// Destructor
	~Stream()
	{
		std::fclose(this->fp);
	}

	// copy assignment operator
	Stream& operator=(const Stream& src) = delete;

	// move assignment operator
	Stream& operator=(Stream&& src)
	{
		fname = src.fname;
		fp = src.fp;
		return *this;
	}

	// overloaded << operator
	Stream& operator << (int input)
	{
		if (input == EOF)
		{
			std::fprintf(fp, "\n");
			std::fflush(fp);
		}
		else
		{
			std::fprintf(fp, "%i", input);
		}
		return *this;
	}
	Stream& operator << (double input)
	{
		std::fprintf(fp, "%f", input);
		return *this;
	}
	Stream& operator << (bool input)
	{
		if (input)
			std::fprintf(fp, "true");
		else
			std::fprintf(fp, "false");
		return *this;
	}
	Stream& operator << (const char * input)
	{
		std::fprintf(fp, "%s", input);
		return *this;
	}
	Stream& operator << (std::string input)
	{
		std::fprintf(fp, "%s", input.c_str());
		return *this;
	}

private:
	const char * fname;
	std::FILE * fp;
};


Stream Cout(stdout);
int Endl = EOF;


int main(int, char**)
{
	Stream s("output.txt");
	// Stream s2 = s; // test that copy construction doesn't compile
	// Stream s2; // test copy assignment doesn't compile
	// s2 = s;

	std::string w = "World!";
	s << "Hello, " << w << "\n";

	Cout << "2 + 2 = " << 2 + 2 << "\n";
	s << "hey" << Endl;
	s << -2 << Endl;
	std::abort();
}
