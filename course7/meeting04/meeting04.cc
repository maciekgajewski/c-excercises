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

	File(const File&) = delete;

	File(File&& other)
	{
		std::cout << "Stealing file" << std::endl;
		mFd = other.mFd;
		other.mFd = -1;
	}

	void write(const std::string& s) /* no const */
	{
		std::cout << "Writing string: " << s << std::endl;
		ssize_t res = ::write(mFd, s.c_str(), s.length());
		if (res < 0)
			throw std::runtime_error("Error writing to file");
	}

	// TODO read
	
	size_t getSize() const
	{
		struct stat out;
		int res = ::fstat(mFd, &out);

		if (res != 0)
			throw std::runtime_error("Error reading the file stats");
		
		return out.st_size;
	}

	~File()
	{
		if (mFd != -1)
		{
			std::cout << "Closing file" << std::endl;
			int res = ::close(mFd);
			if (res != 0)
			{
				std::cerr << "Error closing a file" << std::endl;
			}
		}
		else
		{
			std::cout << "Zombie, not closing" << std::endl;
		}
	}

	File& operator=(File&& other)
	{
		std::cout << "Assiging from another" << std::endl;
		if (mFd != -1)
			::close(mFd);
		mFd = other.mFd;
		other.mFd = -1;
		return *this;
	}

private:

	int mFd;
};

class Logger
{
public:

	Logger(const std::string& path)
		: mFile(path)
	{
		debug("Log open");
	}

	~Logger() { debug("Log closed"); }

	void info(const std::string& message)
	{
		mFile.write("[INFO ] " + message + "\n");
	}

	void debug(const std::string& message)
	{
		mFile.write("[DEBUG] " + message + "\n");
	}

private:

	File mFile;
};


File getBigger(const std::string& path1, const std::string& path2)
{
	File f1(path1), f2(path2);

	if (f1.getSize() > f2.getSize())
		return f1;
	else
		return f2;
}

int main(int argc, char** argv)
{
	if (argc < 2)
		throw std::runtime_error("Arg required");
	
	File g = getBigger("a", "b");
	g.write("This is the bigger file");

	g = getBigger("x", "y");
	g.write("This is another bigger file");

}