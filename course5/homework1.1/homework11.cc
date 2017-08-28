#include <iostream>
#include <vector>
#include <algorithm>


int main(int argc, char** argv)
{
    std::vector<std::string> word_array;
    for (int i= 1; i< argc; ++i) {
        word_array.push_back(argv[i]);
    }
    std::sort (word_array.begin(), word_array.end());
    for (auto &word : word_array) {
        std::cout << word <<std::endl;
    }
}
