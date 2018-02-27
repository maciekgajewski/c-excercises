cmake_minimum_required(VERSION 3.0)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -std=c++14")

find_package(Boost REQUIRED COMPONENTS filesystem)

INCLUDE_DIRECTORIES(${Boost_INCLUDE_DIR})

add_library(plugin_interface STATIC complex_stack.cc complex_stack.hh complex.cc complex.hh)

add_library(print SHARED print.cc)
SET_TARGET_PROPERTIES(print PROPERTIES PREFIX "")
TARGET_LINK_LIBRARIES(print LINK_PUBLIC plugin_interface)

add_executable(complex main.cc calculator.hh calculator.cc)

TARGET_LINK_LIBRARIES(complex LINK_PUBLIC ${Boost_LIBRARIES} dl plugin_interface)
