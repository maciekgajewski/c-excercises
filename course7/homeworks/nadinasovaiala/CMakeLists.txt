cmake_minimum_required(VERSION 3.8)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -std=c++14")

find_package(Boost 1.63.0 REQUIRED COMPONENTS filesystem)
include_directories(${Boost_INCLUDE_DIRS})
add_executable(assign1 assign1.cc)
target_link_libraries(assign1 ${Boost_LIBRARIES})

