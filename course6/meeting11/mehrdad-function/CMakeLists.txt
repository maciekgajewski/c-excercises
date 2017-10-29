project(mehrdad_function)
cmake_minimum_required(VERSION 3.0)

add_executable(mfunction
    function.h function.cc
    test.cc catch.hpp)

set_property(TARGET mfunction PROPERTY CXX_STANDARD 14)

