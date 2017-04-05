set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -std=c++14")
add_executable(homework9.1 homework9.1.cc)
target_link_libraries(homework9.1 benchmark pthread)
