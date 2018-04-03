cmake_minimum_required(VERSION 3.1.1 FATAL_ERROR)

project(fred_calculator)

add_compile_options("-std=c++14" "-Wall" "-Wextra")

find_package(Boost COMPONENTS
  filesystem REQUIRED)

add_executable(calculator
  main.cc
  operator.h
  complex.h
  complex.cc
  plugin.h
  plugin_loader.h
  plugin_loader.cc
  calculator.h
  calculator.cc)

target_link_libraries(calculator PUBLIC Boost::filesystem dl)
