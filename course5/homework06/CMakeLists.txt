cmake_minimum_required(VERSION 3.5)
project(homework06)

add_compile_options(-Wall -Wextra -Weffc++ -Wdisabled-optimization --coverage)
set(CMAKE_CXX_STANDARD 14)

add_executable(homework06
    homework06.cc
    ustring.h
    ustring.cc
    tuple_pretty_print.h)

target_link_libraries(homework06 --coverage)

add_custom_target(coverage
    COMMAND lcov --directory . --zerocounters
    COMMAND ./homework06
    COMMAND lcov --directory . --capture --output-file coverage.info
    COMMAND genhtml coverage.info --output-directory coverage)
add_dependencies(coverage homework06)
