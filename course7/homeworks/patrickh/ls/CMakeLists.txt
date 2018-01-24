cmake_minimum_required(VERSION 3.7.2)
set(CMAKE_CXX_STANDARD 14)
project(ls)

set(Boost_USE_STATIC_LIBS        ON)
set(Boost_USE_MULTITHREADED      ON)
set(Boost_USE_STATIC_RUNTIME    OFF)
find_package(Boost COMPONENTS filesystem REQUIRED)

if(Boost_FOUND)
    include_directories(${Boost_INCLUDE_DIRS})
    add_executable(ls ls.cc)
    target_link_libraries(ls ${Boost_LIBRARIES})
endif()