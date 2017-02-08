#include <iostream>
#include <algorithm>
#include <cstring>

int main(int argc, char** argv)
{
    std::sort(argv, argv + argc,
            [](const char* s1, const char *s2){ return strcmp(s1, s2) < 0; });
    for (int i = 0; i != argc; ++i) {
        std::cout << argv[i] << std::endl;
    }
    return 0;
}
