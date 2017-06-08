find_package(Boost REQUIRED COMPONENTS program_options filesystem)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra")
set(CMAKE_CXX_STANDARD 14)
include_directories(SYSTEM ${Boost_INCLUDE_DIR})

add_executable(meeting17
	meeting17.cc
)

target_link_libraries(meeting17

	${Boost_LIBRARIES}
	pthread
)


