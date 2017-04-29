#include <iostream>
#include <algorithm>
#include <string.h>

int cmpArgv(const char* lhs, const char* rhs)
{
        auto result = strcmp(lhs, rhs);
        return result < 0;
}

int main(int argc, char** argv)
{
        std::sort(argv + 1, argv + argc, cmpArgv);
        for (auto i = 1; i < argc; i++)
        {
                std::cout << argv[i] << std::endl;
        }
}
