#include <iostream>
#include <list>
#include <string>

int main(int argc, char** argv)
{
    std::list<std::string> arg_list;

    for (int i = 0; i < argc; i++)
    {
        arg_list.push_back(argv[i]);
    }

    arg_list.pop_front(); // remove binary name
    arg_list.sort();

    for (auto a : arg_list) {
        std::cout << a << std::endl;
    }
}
