set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -std=c++14")
add_executable(benchmark_greater benchmark.cc)
target_link_libraries(benchmark_greater benchmark pthread)