#include <iostream>

using namespace std;

int main()
{
    std::string s = "1";
    int i = 0;
    const char * c =s.c_str();
    while (c[i] != '\0')
        i++;

    cout << "s.length=" << s.length() << " i=" << i << std::endl;
    return 0;
}

