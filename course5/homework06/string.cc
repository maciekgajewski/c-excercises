#include "string.h"

String::String(char * data)
{
    if (!data)
        throw std::runtime_error("expected non null char* data");
    int i = 0;
    while (data[i] != '\0')
        i++;
    //todo size = power of two

    this->buffer = std::make_unique<char[]>(i);
}
