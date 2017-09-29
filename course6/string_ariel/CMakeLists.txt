cmake_minimum_required(VERSION 2.8)

project(string_ariel)

add_subdirectory(str)

add_executable(${PROJECT_NAME}
    string_tests.cc)

target_link_libraries(string_ariel
    str
    )
