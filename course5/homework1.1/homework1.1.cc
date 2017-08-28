#include <iostream>
#include <algorithm>
#include <cstring>

int main(int argc, char* argv[])
{
    std::sort(argv+1, &argv[argc], [](const char *lhs, const char *rhs) {
                return std::strcmp(lhs, rhs) < 0;
            });
    for (auto n=1; n<argc; ++n)
        std::cout << argv[n] << std::endl;
}
