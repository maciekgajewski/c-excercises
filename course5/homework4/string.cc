#include <iostream>
#include <string>
#include <stdexcept>
#include <cstdio>

class Stream
{
public:

        Stream(const char* filename)
        {
            this->file = std::fopen(filename, "w");
        }

        ~Stream()
        {
            std::fclose(this->file);
        }

private:
        std::FILE* file;
}

int main(int, char**)
{
    Stream f;
}