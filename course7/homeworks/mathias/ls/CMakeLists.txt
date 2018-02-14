cmake_minimum_required(VERSION 3.4 FATAL_ERROR)

project(ls VERSION 1.0 LANGUAGES CXX)

set(Boost_USE_STATIC_LIBS ON)
find_package(Boost COMPONENTS filesystem program_options REQUIRED)

if(MSVC)
    add_compile_options("/permissive-" "/W4" "/wd4505" "/WX" "$<$<CONFIG:RELEASE>:/O2>")
else()
    add_compile_options("-std=c++14" "-Wall" "-Wextra" "-Werror" "$<$<CONFIG:RELEASE>:-O3>")
endif()

add_executable(ls main.cpp)
target_link_libraries(ls PRIVATE Boost::filesystem Boost::program_options)
target_include_directories(ls PRIVATE Boost::boost)
