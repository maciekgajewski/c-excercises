find_package(Boost REQUIRED)
include_directories(${Boost_INCLUDE_DIRS})

add_executable(tests
	tests.cc
	math/vector_tests.cc
	util/unique_ptr_tests.cc)

target_link_libraries(tests
	math
	${Boost_UNIT_TEST_FRAMEWORK_LIBRARY}
)
