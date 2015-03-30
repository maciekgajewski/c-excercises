project(c-excercises)
cmake_minimum_required(VERSION 2.8)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -std=c++11")

add_subdirectory(string)
add_subdirectory(sorted)
add_subdirectory(plot)
add_subdirectory(moo)
