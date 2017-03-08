#include <string>
#include <iostream>
#include <cstdlib>
#include <cstdio>
#include <stdexcept>

struct flush_t {
        const char* value;

        flush_t(const char* value)
        {
                this->value = value;
        }
};

flush_t Endl("\n");


class Stream {
public:
        Stream(FILE* fp)
        {
                this->fp = fp;
        }

        Stream(const char* filename)
        {
                this->filename = filename;
                fp = std::fopen(filename, "w");
                if (fp == nullptr) {
                        throw std::runtime_error("Failed to open file");
                }
        }

        Stream(const std::string& filename)
        {
                Stream(filename.c_str());
        }

        Stream(const Stream& that) = delete;

        Stream(Stream&& that)
        {
                fp = that.fp;
                that.fp = nullptr;
                filename = that.filename;
                that.filename = nullptr;
        }

        ~Stream()
        {
                if (filename != nullptr) {
                        auto result = std::fclose(fp);
                        if (result != 0) {
                                throw std::runtime_error("Failed to properly close file");
                        }
                }
        }

        const Stream& operator<<(int value) const
        {
                std::fprintf(fp, "%d", value);
                return *this;
        }

        const Stream& operator<<(const char* value) const
        {
                std::fprintf(fp, "%s", value);
                return *this;
        }

        const Stream& operator<<(const std::string& value) const
        {
                *this << value.c_str();
                return *this;
        }

        const Stream& operator<<(flush_t value) const
        {
                *this << value.value;
                std::fflush(fp);
                return *this;
        }

        const Stream& operator<<(double value) const
        {
                std::fprintf(fp, "%f", value);
                return *this;
        }

        const Stream& operator<<(unsigned int value) const
        {
                std::fprintf(fp, "%u", value);
                return *this;
        }

        const Stream& operator<<(bool value) const
        {
                if (value) {
                        std::fprintf(fp, "true");
                } else {
                        std::fprintf(fp, "false");
                }
                return *this;
        }

        const Stream& operator<<(const void* value) const
        {
                std::fprintf(fp, "%p", value);
                return *this;
        }

        void Describe(Stream& out) const
        {
                out << "this->fp: " << this->fp << "; this->filename: " << (filename == nullptr ? "<none>" : filename );
        }

private:
        std::FILE* fp;
        const char* filename = nullptr;
};


Stream Cout(stdout);

int main(int, char**)
{
        Stream s("output.txt");
        std::string w = "World!";
        s << "Hello, " << w << Endl;

        Cout << "2 + 2 = " << 2 + 2 << Endl;
        Cout << "3.5 + 3.5 = " << 3.5 + 3.5 << Endl;
        Cout << "1 == 1 = " << (1 == 1) << Endl;

        Stream s2 = std::move(s);
        s2 << "some more text" << Endl;
        Cout << "s moved to s2, old s: ";
        s.Describe(Cout);
        Cout << ", new s2: ";
        s2.Describe(Cout);
        Cout << Endl;

        return 0;
}
