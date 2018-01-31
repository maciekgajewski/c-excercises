cmake_minimum_required(VERSION 3.0)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -std=c++14")

find_package(Boost COMPONENTS filesystem program_options)
include_directories(${Boost_INCLUDE_DIRS})

add_executable(ls main.cc)
target_link_libraries(ls ${Boost_LIBRARIES})
