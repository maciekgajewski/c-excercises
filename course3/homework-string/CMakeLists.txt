set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -std=c++14")

add_executable(string_test
        test.cc
        my_string.cc my_string.h
        )