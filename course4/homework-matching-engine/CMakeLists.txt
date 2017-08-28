cmake_minimum_required(VERSION 3.0 FATAL_ERROR)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -std=c++14")

add_executable(matching_engine
	order_book.cc order_book.hh
	matching_engine.cc
	)

