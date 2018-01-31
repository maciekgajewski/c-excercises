cmake_minimum_required(VERSION 3.0)
project(my_ls)

find_package(Boost 1.55 REQUIRED COMPONENTS filesystem system program_options )

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fexceptions -Wextra -std=c++14")
include_directories(${Boost_INCLUDE_DIRS})
add_executable(ls_hw2 ls_hw2.cpp)
target_link_libraries(ls_hw2 ${Boost_LIBRARIES})
