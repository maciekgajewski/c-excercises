cmake_minimum_required(VERSION 3.0)
enable_testing()
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -std=c++14")

add_executable(complex calculator.cc complex.cc complex_linked_list.cc main.cc)

add_executable(linked_list_test complex.cc complex_linked_list.cc test.cc)
add_test(NAME linked_list_test COMMAND linked_list_test)
