cmake_minimum_required(VERSION 3.0)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -std=c++14")

find_package(Boost COMPONENTS filesystem)
include_directories(${Boost_INCLUDE_DIRS})

add_executable(homework1 homework01.cc)
target_link_libraries(homework1 ${Boost_LIBRARIES})
