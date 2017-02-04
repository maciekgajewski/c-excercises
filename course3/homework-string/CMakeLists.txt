set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -std=c++14")

add_executable(test 
    test.cc
    my_string.cc my_string.h
)