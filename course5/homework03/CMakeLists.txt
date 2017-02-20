set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra ")
set(CMAKE_CXX_STANDARD 14)

add_library(print print.cc)
target_link_libraries(print)
add_executable(homework03 homework03.cc )
target_link_libraries(homework03 print)

