cmake_minimum_required(VERSION 3.0)

project(my_ls)

find_package(Boost 1.55 REQUIRED COMPONENTS filesystem system)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fexceptions -Wextra -std=c++14")
include_directories(${Boost_INCLUDE_DIRS})
add_executable(my_ls my_ls.cpp)
target_link_libraries(my_ls ${Boost_LIBRARIES})

