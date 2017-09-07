set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall")
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

project(toyapp)
cmake_minimum_required(VERSION 3.0)

set(SDL_ROOT "" CACHE STRING "SDL2 Library root path")

if(NOT SDL_ROOT STREQUAL "")
	include_directories(${SDL_ROOT}/include)
	link_directories(${SDL_ROOT}/lib)
endif()

include_directories(${CMAKE_CURRENT_SOURCE_DIR})

add_subdirectory(displaylib)
add_subdirectory(math)
add_subdirectory(util)

add_executable(toyapp WIN32 main.cc)

if(MINGW)
	target_link_libraries(toyapp mingw32)
endif()

target_link_libraries(toyapp
	displaylib
	math
	util
	SDL2main)
