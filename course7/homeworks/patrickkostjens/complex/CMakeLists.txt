cmake_minimum_required(VERSION 3.0)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -std=c++14")

find_package(Boost REQUIRED COMPONENTS filesystem)

INCLUDE_DIRECTORIES(${Boost_INCLUDE_DIR})

add_library(print SHARED print.cc complex.cc complex.hh complex_stack.cc complex_stack.hh)
SET_TARGET_PROPERTIES(print PROPERTIES PREFIX "")

add_executable(complex main.cc calculator.hh calculator.cc complex_stack.hh complex_stack.cc complex.hh complex.cc)

TARGET_LINK_LIBRARIES(complex LINK_PUBLIC ${Boost_LIBRARIES} dl)
