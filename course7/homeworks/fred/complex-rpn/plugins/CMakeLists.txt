cmake_minimum_required(VERSION 3.1.1 FATAL_ERROR)

project(fred_calculator_plugins)

add_compile_options("-std=c++14" "-Wall" "-Wextra")

add_library(average SHARED
  average.cc
  ../complex.h
  ../complex.cc)
