set(CMAKE_CXX_STANDARD 14)
add_executable(mem_access
	mem_access.cc
	get_vector.cc
)

target_link_libraries(mem_access
	benchmark
	pthread
)
