cmake_minimum_required(VERSION 3.0)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -std=c++14")
find_package(Boost COMPONENTS program_options)
include_directories(${Boost_INCLUDE_DIRS})

add_executable(homework12 homework12.cc line_sorter.cc)
target_link_libraries(homework12 ${Boost_LIBRARIES})

add_executable(tests tests.cc line_sorter.cc)
target_link_libraries(tests ${Boost_LIBRARIES})
