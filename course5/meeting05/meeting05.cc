#include <iostream>
#include <string>
#include <cassert>
#include <cstdio>
#include <cstring>

class File
{
public:
	
	enum class Mode { READ, WRITE, APPEND };
	
	File(const std::string& path, Mode mode)
	{
		switch(mode)
		{
		case Mode::READ:
			mFile = std::fopen(path.c_str(), "r");
			break;
		case Mode::WRITE:	
			mFile = std::fopen(path.c_str(), "w");
			break;
		case Mode::APPEND:	
			mFile = std::fopen(path.c_str(), "a");
			break;
		}
		if (!mFile)
		{
			std::string msg = std::strerror(errno);
			throw std::runtime_error("Failed to open a file:" + msg);
		}
	}
	
	~File()
	{
		std::fclose(mFile);
	}
	
	void write(const std::string& s)
	{
		std::fprintf(mFile, "%s", s.c_str());
	}
	
	void write(const char* s)
	{
		std::fprintf(mFile, "%s", s);
	}

private:
	
	FILE* mFile;
};

int main(int /*argc*/, char** /*argv*/)
{
	File f("/output.txt", File::Mode::APPEND);
	f.write("hey\n");
	std::string str = "you!";
	f.write(str);
}

