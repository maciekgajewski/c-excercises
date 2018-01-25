cmake_minimum_required(VERSION 2.8)

project(my_ls)

find_package(Boost COMPONENTS filesystem REQUIRED)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g -fexceptions -Wextra -std=c++14")
add_executable(my_ls my_ls.cpp)

target_link_libraries(my_ls PRIVATE Boost::filesystem)                                                           
target_include_directories(my_ls PRIVATE Boost::boost)             