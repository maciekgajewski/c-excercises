set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -std=c++14")

add_executable(linked_list_test
        test.cc
        linked_list.h
        )