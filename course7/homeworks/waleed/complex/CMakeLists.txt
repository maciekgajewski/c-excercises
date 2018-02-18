cmake_minimum_required(VERSION 2.8)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -std=c++14")

project(complex)
add_executable(${PROJECT_NAME} "main.cpp" "complex.cpp" "complex.h" "calculator.cpp" "calculator.h")
