set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -std=c++14")
add_executable(homework11.2 homework11.2.cc)
target_link_libraries(homework11.2 benchmark pthread)
