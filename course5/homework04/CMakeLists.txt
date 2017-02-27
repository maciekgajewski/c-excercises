set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra ")
set(CMAKE_CXX_STANDARD 14)

add_library(Stream Stream.cc)
add_executable(homework04 homework04.cc )
target_link_libraries(homework04 Stream)

