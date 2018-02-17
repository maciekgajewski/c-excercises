cmake_minimum_required(VERSION 3.0.0)
set(CMAKE_CXX_STANDARD 14)
project(ls)

find_package(Boost COMPONENTS filesystem program_options REQUIRED)

include_directories(${Boost_INCLUDE_DIRS})
add_executable(ls ls.cc)
target_link_libraries(ls ${Boost_LIBRARIES})