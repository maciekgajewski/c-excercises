project(homework09)
cmake_minimum_required(VERSION 3.2)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -lboost_program_options")
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_BUILD_TYPE Release)
include_directories(~/google-benchmark/benchmark/include)

add_executable(${PROJECT_NAME} homework09-1.cc)
add_executable(homework09-2 homework09-2.cc)

target_link_libraries(${PROJECT_NAME} -static-libgcc -static-libstdc++ /home/alexey/google-benchmark/build/src/libbenchmark.a pthread)

configure_file(data.txt data.txt COPYONLY)

