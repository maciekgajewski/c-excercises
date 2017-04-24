cmake_minimum_required(VERSION 3.5)
project(homework10)

add_compile_options(-Wall -Wextra -Weffc++ -Wdisabled-optimization --coverage)
set(CMAKE_CXX_STANDARD 14)

add_executable(homework10
    linkedlist.hh
    homework10.cc)

target_link_libraries(homework10 --coverage)

add_custom_target(coverage
    COMMAND lcov --directory . --zerocounters
    COMMAND ./homework10
    COMMAND lcov --directory . --capture --output-file coverage.info
    COMMAND genhtml coverage.info --output-directory coverage)
add_dependencies(coverage homework10)
