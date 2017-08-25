project(homework09)
cmake_minimum_required(VERSION 3.2)
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_BUILD_TYPE Release)

add_subdirectory(x_benchmark EXCLUDE_FROM_ALL)
include_directories(x_benchmark/include)

add_executable(${PROJECT_NAME} homework09-1.cc)
add_executable(homework09-2 homework09-2.cc unique_ptr.h)

target_link_libraries(${PROJECT_NAME} -static-libgcc -static-libstdc++ benchmark pthread)

configure_file(data.txt data.txt COPYONLY)

