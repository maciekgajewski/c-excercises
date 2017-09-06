project(toyapp)
cmake_minimum_required(VERSION 3.0)

add_subdirectory(displaylib)

add_executable(toyapp WIN32
	main.cc)

set_property(TARGET toyapp PROPERTY CXX_STANDARD 14)

target_link_libraries(toyapp
	displaylib
	SDL2main
	)

include(FindOpenMP)
if(OPENMP_FOUND)
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} ${OpenMP_C_FLAGS}")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${OpenMP_CXX_FLAGS}")
    set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} ${OpenMP_EXE_LINKER_FLAGS}")
else(OPENMP_FOUND)
    message("ERROR: OpenMP could not be found.")
endif(OPENMP_FOUND)
