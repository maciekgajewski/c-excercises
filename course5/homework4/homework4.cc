
#include <string>
#include <cstdio>
#include <cstdlib>

struct EndOfLine { };

class Stream
{
public:
	Stream(const char* fileName)
	{
		fp = std::fopen(fileName, "w");
	}

	Stream() = delete;
	Stream(const Stream&) = delete;
	Stream(Stream&&) = delete;
	Stream& operator=(const Stream&) = delete;
	Stream& operator=(Stream&&) = delete;

	~Stream()
	{
		std::fclose(fp);
	}

	Stream& operator<<(int i)
	{
		std::fprintf(fp, "%d", i);
		return *this;
	}

	Stream& operator<<(double f)
	{
		std::fprintf(fp, "%f", f);
		return *this;
	}

	Stream& operator<<(char c)
	{
		std::fprintf(fp, "%c", c);
		return *this;
	}

	Stream& operator<<(const std::string& str)
	{
		std::fprintf(fp, "%s", str.c_str());
		return *this;
	}

	Stream& operator<<(EndOfLine)
	{
		std::fprintf(fp, "\n");
		std::fflush(fp);
		return *this;
	}

private:
	std::FILE* fp;
};

Stream Cout("/dev/stdout");
EndOfLine Endl;

int main(int /* argc */, char** /* argv */)
{
	Stream s("output.txt");
	std::string w = "World!";
	s << "Hello, " << w << Endl;

	Cout << "2 + 2 = " << 2 + 2 << Endl;
}
