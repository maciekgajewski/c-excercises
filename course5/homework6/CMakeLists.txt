set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -std=c++14")
project(string)
add_executable(string string.h string.cc main.cc)