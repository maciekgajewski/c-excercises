set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra")
set(CMAKE_CXX_STANDARD 14)
add_executable(meeting10
	meeting10.cc)

add_executable(string_comp_benchmark
	string_comp_benchmark.cc
)

target_link_libraries(string_comp_benchmark
	benchmark
	pthread
)
