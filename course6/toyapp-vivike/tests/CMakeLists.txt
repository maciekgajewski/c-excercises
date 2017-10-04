cmake_minimum_required(VERSION 2.8)

project(displaylib_tests)

find_package(Boost REQUIRED)
include_directories(${Boost_INCLUDE_DIRS})

set(CMAKE_CXX_STANDARD 14)

add_subdirectory(displaylib
	tests)

add_executable(${PROJECT_NAME}
    test_objects.cc)

target_link_libraries(displaylib 
	SDL2 
	tests
	toyapp)