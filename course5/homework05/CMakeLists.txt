project(homework05)
cmake_minimum_required(VERSION 2.8)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra")
set(CMAKE_CXX_STANDARD 14)

include_directories(${SOURCE_DIR})
add_executable(homework05 homework05.cc)
