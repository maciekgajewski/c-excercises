set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra")
set(CMAKE_CXX_STANDARD 14)

include_directories(/Users/sophia/Projects/cpp/benchmark/include)

add_executable(str_benchmark main.cc)
target_link_libraries(str_benchmark
	/Users/sophia/Projects/cpp/benchmark/src/libbenchmark.a
	pthread
)
