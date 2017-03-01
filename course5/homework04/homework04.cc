// Example program
#include <string>
#include <cstdio>
#include <cstdlib>

class Endl
{
};


class Stream
{    
private:
        std::FILE * file;
public:
        static Endl endl;

        Stream()
        {
                file = stdout;
        }

        Stream(const char * filename)
	{
                file = std::fopen(filename, "w");
	}

	~Stream()
	{
                if (file != stdout)
                        std::fclose(file);
	}

	Stream& operator << (std::string value)
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

int main(int argc, char** argv)
{

        Stream Cout;

        if (argc > 1)
                Cout = Stream(argv[1]);

        Cout << std::string(argv[1]) << Stream::endl;

	// comment indicates the expected input
        Cout << 7 << 5 << Stream::endl; // 75
        Cout << true;// true
        Cout << 1.0/3.0;// 0.33
	
	std::string s = "world!";
        Cout << "hello, "; // hello,
        Cout << s; // world!
        Cout << Stream::endl;
	
	float f = 6;
        Cout << f; // 6
        Cout << Stream::endl;
}

