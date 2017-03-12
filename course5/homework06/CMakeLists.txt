project(homework06)
cmake_minimum_required(VERSION 2.8)
aux_source_directory(. SRC_LIST)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra")
set(CMAKE_CXX_STANDARD 14)

include_directories(${SOURCE_DIR})
add_executable(${PROJECT_NAME} ${SRC_LIST})

