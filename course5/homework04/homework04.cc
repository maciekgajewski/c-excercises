#include <cstdio>
#include <cstdlib>
#include <string>
#include <cstring>


struct FlushEndl
{

};

class Stream
{
public:
    Stream(const std::string &OutFileName)
    {
        output_file = std::fopen(OutFileName.c_str(), "w");
    }

    Stream(const Stream& other) = delete;

    ~Stream()
    {
        std::fclose(output_file);
    }

    Stream& operator <<(int i)
    {
        std::fprintf(output_file, "%d", i);
        return *this;
    }

    Stream& operator <<(const char* &Output)
    {
        std::fprintf(output_file, "%s", Output);
        return *this;
    }

    Stream& operator <<(const std::string &Output)
    {
        std::fprintf(output_file, "%s", Output.c_str());
        return *this;
    }

    Stream& operator <<(FlushEndl)
    {
        std::fprintf(output_file, "%s", "\n");
        std::fflush(output_file);
        return *this;
    }

    Stream& operator =(Stream &&src)
    {
        output_file = src.output_file;
        src.output_file = nullptr;
        return *this;
    }

private:
    FILE* output_file;
};


Stream Cout("/dev/stdout");
FlushEndl Endl;


int main()
{
    Stream s("output.txt");
    std::string w = "Wolrd!";
    s << "Hello, " << w;

    Cout << "2+2 = " << 2+2 << "\n";

    Stream f("file.txt");
    f << "hey" << Endl;
}

