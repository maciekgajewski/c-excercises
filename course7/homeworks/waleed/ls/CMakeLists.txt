cmake_minimum_required(VERSION 3.9)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -std=c++14")

project (LS)

find_package(Boost COMPONENTS filesystem system)

include_directories(${Boost_INCLUDE_DIRS})
link_directories(${Boost_LIBRARY_DIRS})

add_executable(ls main.cc)

target_link_libraries(ls ${Boost_LIBRARIES})
