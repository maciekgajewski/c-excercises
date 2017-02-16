set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra")
set(CMAKE_CXX_STANDARD 14)

add_executable(meeting03 meeting03.cc)

add_executable(sqrt_benchmark sqrt_benchmark.cc)
target_link_libraries(sqrt_benchmark
#	/home/maciejgajewski/software/benchmark-debug/src/libbenchmark.a
	benchmark
	pthread
)
