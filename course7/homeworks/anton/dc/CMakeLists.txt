cmake_minimum_required(VERSION 3.0)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -std=c++14")

PROJECT(dc)
  find_package(Boost REQUIRED COMPONENTS filesystem)

  add_executable(dc operation.h stack.h main.cc complex.cc)
  target_link_libraries(dc ${CMAKE_DL_LIBS} ${Boost_LIBRARIES})

  add_library(add SHARED operation_add.cc)
  set_target_properties(add PROPERTIES PREFIX "")

  add_library(substract SHARED operation_substract.cc)
  set_target_properties(substract PROPERTIES PREFIX "")

  add_library(multiply SHARED operation_multiply.cc)
  set_target_properties(multiply PROPERTIES PREFIX "")

  add_library(divide SHARED operation_divide.cc)
  set_target_properties(divide PROPERTIES PREFIX "")
