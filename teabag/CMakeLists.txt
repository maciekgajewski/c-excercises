project(teabag)
cmake_minimum_required(VERSION 3.0)

find_package(Qt5Widgets REQUIRED)
find_package(Boost REQUIRED)

include_directories(${Boost_INCLUDE_DIRS})

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -std=c++14")

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_INCLUDE_CURRENT_DIR ON)

add_executable(teabag

	main.cc
	debugger.cc debugger.hh
	debugger_state.cc debugger_state.hh
	types.cc types.hh
)

target_link_libraries(teabag

	Qt5::Widgets
)

