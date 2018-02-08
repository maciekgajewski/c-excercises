#include <string>
#include <iostream>
#include <stdexcept>
// - read string
// - write string
// - check size
class File
{
public:

	explicit File(const std::string& path /*, mode*/)
	{
		std::cout << "Opening file at: " << path << std::endl;
		// TODO implement, open the file
	}

	void write(const std::string& s) /* no const */
	{
		std::cout << "Writing string: " << s << std::endl;
		// TODO implement
	}

	// TODO read
	// TODO getSize

	~File()
	{
		// TODO
		std::cout << "Closing file" << std::endl;
	}

private:

	int mFd;
};

int main(int argc, char** argv)
{
	if (argc < 2)
		throw std::runtime_error("Arg required");
	
	File f(argv[1]);
	f.write("Hello!");
}