// Example program
#include <string>
#include <cstdio>
#include <cstdlib>
#include <fstream>
#include <cassert>
#include <sstream>

class Endl
{
};


class Stream
{    
private:
        std::FILE * file;
public:
        static Endl endl;

        Stream() = delete;

        Stream(FILE * file) : file(file) { }

        Stream(const char * filename)
	{
                file = std::fopen(filename, "w");
	}

        Stream(Stream&& source)
        {
                file = source.file;
                source.file = nullptr;
        }

        Stream(const Stream& other) = delete;

	~Stream()
        {
                if (file && file != stdout && file != stdin && file != stderr)
                    std::fclose(file);
	}

        Stream& operator = (Stream&& stream)
        {
                file = stream.file;
                stream.file = nullptr;
                return *this;
        }

	Stream& operator << (const char * value)
	{
		std::fprintf(file, "%s", value);
		return *this;
	}

	Stream& operator << (const std::string& value)
	{
		std::fprintf(file, "%s", value.c_str());
                return *this;
	}

        Stream& operator << (bool value)
        {
                std::fprintf(file, "%s", value ? "true" : "false");
                return *this;
        }

        Stream& operator << (int value)
        {
                std::fprintf(file, "%d", value);
                return *this;
        }

        Stream& operator << (float value)
        {
                //std::string format = std::string("%.") + std::to_string(precision).c_str() + std::string("f");
                std::fprintf(file, "%f", value);
                return *this;
        }

        Stream& operator << (double value)
        {
                std::fprintf(file, "%f", value);
                return *this;
        }

        Stream& operator << (Endl)
        {
                std::fprintf(file, "\n");
                std::fflush(file);
                return *this;
        }

};

void test(Stream& cout)
{
        // comment indicates the expected input
        cout << 7 << 5 << Stream::endl; // 75
        cout << true;// true
        cout << 1.0/3.0;// 0.33

        std::string s = "world!";
        cout << "hello, "; // hello,
        cout << s; // world!
        cout << Stream::endl;

        float f = 6;
        cout << f; // 6
        cout << Stream::endl;
}

void create_write_close(const char * fname)
{
	auto cout = Stream(fname);
	test(cout);
}

void do_magic_from_stackoverflow(const char * fname, std::string expected)
{
	std::ifstream t(fname);
	std::stringstream buffer;
	buffer << t.rdbuf();
	auto actual = buffer.str();
	auto cout = Stream(stdout);
	//cout << actual << Stream::endl;
	//std::stringstream buffer;
	assert(actual == expected); 	
}

void test_file()
{
	auto fname = "test.test";
	auto expected = "75\ntrue0.333333hello, world!\n6.000000\n";
	create_write_close(fname);
	do_magic_from_stackoverflow(fname, expected);
}

int main(int , char** )
{
	test_file();
}

