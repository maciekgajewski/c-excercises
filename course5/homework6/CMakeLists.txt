set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra ")
set(CMAKE_CXX_STANDARD 14)

add_executable(homework06_mystr homework06_mystr.cc mystr.h mystr.cc )
add_executable(homework06_stdstr homework06_stdstr.cc mystr.h mystr.cc )

