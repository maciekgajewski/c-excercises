#include <iostream>
#include <list>
#include <string>

int main(int argc, char** argv)
{
    std::list<std::string> arg_list;

    for (int i = 1; i < argc; i++) // ignore argv[0], the binary
    {
        arg_list.push_back(argv[i]);
    }

    arg_list.sort();
    for (auto a : arg_list) {
        std::cout << a << std::endl;
    }
}
