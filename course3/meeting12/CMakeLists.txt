set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -std=c++14")

find_package(Boost REQUIRED)

include_directories(${Boost_INCLUDE_DIRS})

add_executable(meeting12
	meeting12.cc
)

