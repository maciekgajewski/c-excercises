cmake_minimum_required(VERSION 3.5)
project(homework09)

add_subdirectory(x_benchmark)
include_directories(SYSTEM x_benchmark/include)

add_compile_options(-Wall -Wextra -Weffc++)
set(CMAKE_CXX_STANDARD 14)

add_executable(homework09
    homework09.cc)
target_link_libraries(homework09 benchmark)
