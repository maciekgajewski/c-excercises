cmake_minimum_required(VERSION 2.8)

project(string_ariel)

find_package(Boost REQUIRED)
include_directories(${Boost_INCLUDE_DIRS})

set(CMAKE_CXX_STANDARD 14)

add_subdirectory(str)

add_executable(${PROJECT_NAME}
    string_tests.cc)

target_link_libraries(string_ariel
    str
    )
