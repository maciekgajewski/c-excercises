set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -std=c++14")

add_executable(test 
    test.cc
    unique_ptr.h unique_ptr.cc
)