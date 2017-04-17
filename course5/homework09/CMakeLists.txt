set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra --std=c++14")
set(CMAKE_CXX_STANDARD 14)

add_subdirectory(x_benchmark EXCLUDE_FROM_ALL)
include_directories(x_benchmark/include)
add_executable(homework09 homework09.cc)
target_link_libraries(homework09 benchmark)
