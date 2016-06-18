
cmake_minimum_required (VERSION 3.5 )

set(CMAKE_CXX_FLAGS "-std=c++14 -Wall")


find_package( Boost 1.6 COMPONENTS program_options REQUIRED)

include_directories (
    "$PROJECT_SOURCE_DIR/headers/catch"
    ${Boost_INCLUDE_DIR}
)


add_executable(listmain
	list-main.cc
)
target_link_libraries( listmain ${Boost_LIBRARIES} )

add_executable(tests-of-list
    unit-test-runner.cc
    tests-of-list.cc
)
