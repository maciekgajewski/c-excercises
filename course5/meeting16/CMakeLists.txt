find_package(Boost REQUIRED COMPONENTS program_options filesystem)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra")
set(CMAKE_CXX_STANDARD 14)
include_directories(${Boost_INCLUDE_DIR})

add_executable(meeting16
	meeting16.cc)

target_link_libraries(meeting16

	${Boost_LIBRARIES}
)


