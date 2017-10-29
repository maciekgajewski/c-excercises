cmake_minimum_required(VERSION 2.8)

project(toyapp_tests)

find_package(Boost REQUIRED)
include_directories(${Boost_INCLUDE_DIRS})

set(CMAKE_CXX_STANDARD 14)

add_directory(tests)

add_executable(tests
	test_objects.cc
	test_vector.cc
	test_matrix.cc
	)

target_link_libraries(displaylib 
	SDL2 
	tests)