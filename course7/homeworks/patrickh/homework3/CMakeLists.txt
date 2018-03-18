cmake_minimum_required(VERSION 3.0.0)
set(CMAKE_CXX_STANDARD 14)
project(calculator)

include_directories(${Boost_INCLUDE_DIRS})
add_executable(calculator complex_linked_list.cpp complex_linked_list_node.h complex_linked_list.h complex.cpp complex.h calculator.cpp calculator.h main.cpp)
