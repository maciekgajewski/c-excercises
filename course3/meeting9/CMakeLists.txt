set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -std=c++14")

add_executable(bench
	benchmark.cc
)

target_link_libraries(bench
	benchmark
	pthread
)
