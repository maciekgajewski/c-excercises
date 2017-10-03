#find_package(Boost COMPONENTS unit_test_framework REQUIRED)
find_package(Boost REQUIRED)
include_directories(${Boost_INCLUDE_DIRS})

add_executable(tests
	math/vector_tests.cc)

target_link_libraries(tests
	math
	${Boost_UNIT_TEST_FRAMEWORK_LIBRARY}
)
