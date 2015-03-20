#include "log.h"

#include <iostream>

void Logger::log(std::string msg)
{
    std::cout << "LOG: " << msg << std::endl;
}
