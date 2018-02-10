cmake_minimum_required(VERSION 3.1.1 FATAL_ERROR)

project(fred_ls)

add_compile_options("-std=c++14" "-Wall" "-Wextra" "-Werror")

find_package(Boost COMPONENTS
    filesystem REQUIRED
    program_options REQUIRED)

add_executable(ls main.cc)

target_link_libraries(ls PUBLIC Boost::filesystem Boost::program_options)
