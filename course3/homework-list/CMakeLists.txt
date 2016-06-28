set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -std=c++14")

find_package(Boost REQUIRED)

include_directories(${Boost_INCLUDE_DIRS})

add_executable(test
	list.h test.cc
)

add_executable(bench
	list.h benchmark.cc
)

link_directories(/usr/local/lib)

target_link_libraries(bench
	benchmark
	pthread
)