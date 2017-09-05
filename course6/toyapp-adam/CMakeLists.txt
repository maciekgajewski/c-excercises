set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall")

project(toyapp)
cmake_minimum_required(VERSION 3.0)

set(SDL_ROOT "" CACHE STRING "SDL2 Library root path")

include_directories(${SDL_ROOT}/include)
include_directories(${CMAKE_CURRENT_SOURCE_DIR})
link_directories(${SDL_ROOT}/lib)

add_subdirectory(displaylib)
add_subdirectory(math)
add_subdirectory(util)

add_executable(toyapp WIN32 main.cc)
set_property(TARGET toyapp PROPERTY CXX_STANDARD 14)

target_link_libraries(toyapp
#	mingw32                    # HACK, @todo REMOVE and FIX!!
	displaylib
	math
	util
	SDL2main)
