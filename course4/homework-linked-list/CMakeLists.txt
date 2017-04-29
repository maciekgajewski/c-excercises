cmake_minimum_required(VERSION 3.0 FATAL_ERROR)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(linked_list_homework
	test.cc
	linked_list.cc linked_list.hh
	count_until.hh
	)

