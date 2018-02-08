#include <string>
#include <iostream>
#include <stdexcept>

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

// - read string
// - write string
// - check size
class File
{
public:

	explicit File(const std::string& path /*, mode*/)
	{
		std::cout << "Opening file at: " << path << std::endl;
		mFd = ::open(path.c_str(), O_APPEND|O_CREAT|O_RDWR, 0666);
		if (mFd < 0)
			throw std::runtime_error("Failed opening the file");
	}

	void write(const std::string& s) /* no const */
	{
		std::cout << "Writing string: " << s << std::endl;
		ssize_t res = ::write(mFd, s.c_str(), s.length());
		if (res < 0)
			throw std::runtime_error("Error writing to file");
	}

	// TODO read
	// TODO getSize

	~File()
	{
		std::cout << "Closing file" << std::endl;
		int res = ::close(mFd);
		if (res != 0)
		{
			std::cerr << "Error closing a file" << std::endl;
		}
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