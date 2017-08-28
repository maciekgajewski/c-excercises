set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra")
set(CMAKE_CXX_STANDARD 14)

add_executable(is_greater_benchmark main.cc)

target_link_libraries(is_greater_benchmark
	benchmark
	pthread
)

