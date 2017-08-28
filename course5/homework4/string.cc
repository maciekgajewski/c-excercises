#include <iostream>
#include <string>
#include <stdexcept>
#include <cstdio>
#include <cstdlib>

class Flush
{
public:
        Flush(const char* end)
        {
            this->last = end;
        }

        const char* Get()
        {
            return this->last;
        }

private:
        const char* last;
};

class Stream
{
public:
        Stream(const char* filename)
        {
            this->file = std::fopen(filename, "w");
            if (!this->file)
            {
                throw std::runtime_error("File opening failed");
            }
        }

        Stream(std::FILE* file)
        {
            this->file = file;
            if (!this->file)
            {
                throw std::runtime_error("File opening failed");
            }
        }

        Stream(const Stream&) = delete;

        Stream(Stream&&) = delete;

        Stream& operator=(const Stream&) = delete;

        Stream& operator=(Stream&&) = delete; 

        Stream& operator<<(const std::string& x)
        {
            std::fprintf(this->file, "%s", x.c_str());
            return *this;
        }

        Stream& operator<<(const char* x)
        {
            std::fprintf(this->file, "%s", x);
            return *this;
        }

        Stream& operator<<(int x)
        {
            std::fprintf(this->file, "%d", x);
            return *this;
        }

        Stream& operator<<(long x)
        {
            std::fprintf(this->file, "%ld", x);
            return *this;
        }

        Stream& operator<<(bool x)
        {
            std::fprintf(this->file, "%s", x ? "true" : "false");
            return *this;
        }

        Stream& operator<<(double x)
        {
            std::fprintf(this->file, "%f", x);
            return *this;
        }

        Stream& operator<<(Flush endl)
        {
            std::fprintf(this->file, "%s", endl.Get());
            std::fflush(this->file);
            return *this;
        }


        ~Stream()
        {
            std::fclose(this->file);
        }

private:
        std::FILE* file;
};

Stream Cout(stdout);
Flush Endl("\n");

int main(int, char**)
{
    std::string w =  "World!";
    Stream s("new_file.txt");
    s << "Hello, " << w; // content does not appear in the file due to quick_exit
    
    Cout << "2 + 2 = " << 2 + 2 << "\n";
    
    Stream f("text.txt");
    f << "hey" << Endl; //content does appear in the file because of Endl
    
    std::quick_exit(1); //to test Endl
}