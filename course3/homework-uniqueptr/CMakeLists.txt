set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -std=c++1y")

add_executable(test
	test.cc unique_ptr.cc
)


