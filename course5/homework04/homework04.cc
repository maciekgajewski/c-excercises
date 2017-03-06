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
	Stream() = delete; // default
	Stream(const Stream&) = delete; // copy
	Stream(Stream&& src) = delete; // move

	Stream(const char* initFname)
	{
		fname = initFname;
		fp = std::fopen(fname, "a");
		if (!fp)
		{
			std::string msg = std::strerror(errno);
			throw std::runtime_error("Failed to open file: " + msg);
		}
	}
	Stream(std::FILE *)
	{
		fp = stdout;
	}

	// Destructor
	~Stream()
	{
		if (fp)
			std::fclose(fp);
	}

	// copy assignment operator
	Stream& operator=(const Stream& src) = delete;

	// move assignment operator
	Stream& operator=(Stream&& src) = delete;

	// overloaded << operator
	const Stream& operator << (int input) const
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
	const Stream& operator << (double input) const
	{
		std::fprintf(fp, "%f", input);
		return *this;
	}
	const Stream& operator << (bool input) const
	{
		if (input)
			std::fprintf(fp, "true");
		else
			std::fprintf(fp, "false");
		return *this;
	}
	const Stream& operator << (const char * input) const
	{
		std::fprintf(fp, "%s", input);
		return *this;
	}
	const Stream& operator << (std::string input) const
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

void yolo(const Stream& s)
{
	s << "Yolo" << Endl;
}

int main(int, char**)
{
	Stream s("output.txt");
	// Stream s2; // test that default construction doesn't compile
	// Stream s2 = s; // test that copy construction doesn't compile
	// Stream s2; // test copy assignment doesn't compile
	// s2 = s;

	// Stream s2("/etc/passwd"); // test that file-open error checking is working
	// s2 << "YOLO!" << Endl;

	// Stream sToMove("another2.txt"); // test that move construction doesn't compile
	// Stream s2 = std::move(sToMove);

	// Stream sToMove("another2.txt"); // test that move assignment doesn't compile
	// s = std::move(sToMove);

	std::string w = "World!";
	s << "Hello, " << w << "\n";

	Cout << "2 + 2 = " << 2 + 2 << "\n";
	s << "hey" << Endl;
	s << -2 << Endl;
	yolo(s);

	// std::abort();
}
