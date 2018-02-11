cmake_minimum_required(VERSION 3.0)
set(SOURCES main.cc complex.cc)
set(HEADERS complex.h)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -std=c++14")

find_package(Boost COMPONENTS filesystem program_options)
include_directories(${Boost_INCLUDE_DIRS})

add_executable(dc ${HEADERS} ${SOURCES} )
target_link_libraries(dc ${Boost_LIBRARIES})
