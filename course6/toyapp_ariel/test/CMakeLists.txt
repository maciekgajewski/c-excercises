project(test)

cmake_minimum_required(VERSION 3.0)

set_property(TARGET displaylib PROPERTY CXX_STANDARD 14)

find_package(Boost REQUIRED)
include_directories(${Boost_INCLUDE_DIRS})

add_executable(unittests unittests.cc)

target_link_libraries(unittests displaylib)
