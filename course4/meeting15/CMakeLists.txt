set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -std=c++14 -Wno-deprecated-declarations")
find_package(Boost)

include_directories(${Boost_INCLUDE_DIR})
add_executable(meeting15 meeting15.cc)

target_link_libraries(meeting15

	pthread rt
)


