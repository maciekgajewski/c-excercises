set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -std=c++14")
find_package(Boost)

include_directories(${Boost_INCLUDE_DIR})
add_executable(meeting10 meeting10.cc)


