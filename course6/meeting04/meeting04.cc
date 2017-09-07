#include <iostream>
#include <string>

class File
{
public:

	File() = default;
	File(const std::string& path)
	{
		name = path;
		std::cout << "opening file " << path << std::endl;
	}

	File( const File&) = delete;
	File& operator=(const File&) = delete;

	~File()
	{
		if (name.empty())
			std::cout << "~File: file not open" << std::endl;
		else
			std::cout << "closing file " << name << std::endl;
	}

	File(File&& other)
	{
		name = other.name;
		other.name = "";
	}

private:

	std::string name;
};

File loadPathFromConfigAndOpen()
{
	File config("cfg.ini");
	std::cout << "loading config..." << std::endl;
	return config;
}

int main(int argc, char** argv)
{
	File f("one.cpp");
	File f2("file.txt");

	File f4(std::move(f2));

	File f3 = loadPathFromConfigAndOpen();
	std::cout << "confdig loaded!" << std::endl;
}

