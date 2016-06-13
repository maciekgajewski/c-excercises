
cmake_minimum_required (VERSION 3.5 )

set(CMAKE_CXX_FLAGS "-std=c++14 -Wall")

add_executable(listmain
	list-main.cc
)

add_executable(tests-of-list
    tests-of-list.cc
)

include_directories ( "$PROJECT_SOURCE_DIR/headers/catch" )
