set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -std=c++1y")

add_executable(test
	test.cc my_string.cc
)

add_executable(test2
	test2.cc my_string.cc
)


