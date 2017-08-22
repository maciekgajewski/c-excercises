#include <iostream>

#include <displaylib/window.h>
#include <displaylib/functions.h>

int main()
{
    std::cout << "Hello" << std::endl;

    Display::Window w("Hello", 10, 10, 800, 600);
    Display::Delay(1000);

    return 0;
}