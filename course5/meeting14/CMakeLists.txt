find_package(Boost REQUIRED)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra")
set(CMAKE_CXX_STANDARD 14)
include_directories(${Boost_INCLUDE_DIR})

add_executable(meeting14
	meeting14.cc)

	

