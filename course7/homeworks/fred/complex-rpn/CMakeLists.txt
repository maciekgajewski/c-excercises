cmake_minimum_required(VERSION 3.1.1 FATAL_ERROR)

project(fred_calculator)

add_compile_options("-std=c++14" "-Wall" "-Wextra")

add_executable(calculator
  main.cc
  complex.h
  complex.cc
  calculator.h
  calculator.cc
  utils.h)
