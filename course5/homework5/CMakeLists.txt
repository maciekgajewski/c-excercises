set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -std=c++14")
project(vector)
add_executable(vector vector.h vector.cc main.cc)