project(homework12)
cmake_minimum_required(VERSION 3.2)

find_package(Boost REQUIRED COMPONENTS program_options)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -lboost_program_options")
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_BUILD_TYPE Debug)
include_directories(${Boost_INCLUDE_DIR})

add_executable(${PROJECT_NAME} homework12.cc comparers.h)

target_link_libraries(${PROJECT_NAME} -static-libgcc -static-libstdc++ ${Boost_LIBRARIES})

add_executable(tests tests.cpp comparers.h)
