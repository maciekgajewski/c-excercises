set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -std=c++17")
#set(CMAKE_CXX_STANDARD 17)

add_executable(homework06
    homework06.cc
    ustring.h
    ustring.cc
    tuple_pretty_print.h)
