cmake_minimum_required(VERSION 3.0)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -std=c++14")

PROJECT(dc)
  set(SOURCES main.cc complex.cc complex_stack.cc)
  set(HEADERS complex.h complex_stack.h)

  add_executable(dc ${HEADERS} ${SOURCES} )
