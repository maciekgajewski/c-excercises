#include <cstdio>
#include <string>
#include <cstring>
#include <cassert>
#include <tuple>
#include <cerrno>

class StreamWriter
{
public:
    StreamWriter(std::string const &filename, std::string const &mode="w")
    {
        mFile = std::fopen(filename.c_str(), mode.c_str());
        if (mFile == nullptr)
            throw std::runtime_error(std::strerror(errno));
    }

    StreamWriter(StreamWriter &&rhs)
    {
        mFile = rhs.mFile;
        rhs.mFile = nullptr;
    }

    StreamWriter(StreamWriter const &) = delete;
    StreamWriter& operator=(StreamWriter const &) = delete;

    ~StreamWriter()
    {
        if (mFile)
            std::fclose(mFile);
    }

    StreamWriter& operator<<(bool b)
    {
        if (std::fprintf(mFile, b ? "true" : "false") < 0)
            throw std::runtime_error(std::strerror(errno));
        return *this;
    }

    StreamWriter& operator<<(int i)
    {
        if (std::fprintf(mFile, "%d", i) < 0)
            throw std::runtime_error(std::strerror(errno));
        return *this;
    }

    StreamWriter& operator<<(double d)
    {
        if (std::fprintf(mFile, "%lg", d) < 0)
            throw std::runtime_error(std::strerror(errno));
        return *this;
    }

    StreamWriter& operator<<(char const *str)
    {
        if (std::fprintf(mFile, "%s", str) < 0)
            throw std::runtime_error(std::strerror(errno));
        return *this;
    }

    StreamWriter& operator<<(std::string const &str)
    {
        if (std::fprintf(mFile, "%s", str.c_str()) < 0)
            throw std::runtime_error(std::strerror(errno));
        return *this;
    }

    void flush()
    {
        std::fflush(mFile);
    }
private:
    FILE *mFile;
};

StreamWriter& Endl(StreamWriter &writer)
{
    writer << "\n";
    writer.flush();
    return writer;
}

StreamWriter& operator<<(StreamWriter &writer, StreamWriter& (*Manipulator)(StreamWriter&))
{
    return Manipulator(writer);
}

void test_move(StreamWriter writer)
{
    writer << "Mokus felmaszott a fara." << Endl;
}

int main()
{
    StreamWriter s("/dev/stdout");
    std::string w = "World!";
    s << "Hello, " << w << "\n";
    s << "2 + 2 = " << 2 + 2 << "\n";
    test_move(std::move(s));

    StreamWriter s2("output.txt");
    s2 << "hey" << Endl << "test" << Endl;
    std::quick_exit(1);
}
