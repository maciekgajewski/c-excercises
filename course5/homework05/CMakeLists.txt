project(homework05)
cmake_minimum_required(VERSION 3.0)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra")
set(CMAKE_CXX_STANDARD 14)
file(GLOB homework05_source "*.h" , "*.cc")

include_directories(${SOURCE_DIR})
add_executable(homework05 ${homework05_source})
