cmake_minimum_required(VERSION 3.0.0)
set(CMAKE_CXX_STANDARD 14)
project(calculator)

find_package(Boost COMPONENTS filesystem program_options REQUIRED)

include_directories(${Boost_INCLUDE_DIRS})
add_executable(calculator complex.cpp complex.h calculator.cpp calculator.h)
target_link_libraries(calculator ${Boost_LIBRARIES})