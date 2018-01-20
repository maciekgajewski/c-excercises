cmake_minimum_required(VERSION 3.5)

find_package(Boost REQUIRED COMPONENTS filesystem)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -std=c++14")

add_executable(ls ls.cc)
target_link_libraries(ls Boost::filesystem)
