set(CMAKE_CXX_STANDARD 14)

add_executable(list-vector-becnhmark

	list-vector.cc
)

target_link_libraries(list-vector-becnhmark

	benchmark
	pthread
)