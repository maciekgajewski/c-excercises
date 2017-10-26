file(GLOB test_sources *.cc)

add_executable(tests ${test_sources})

set_property(TARGET tests PROPERTY CXX_STANDARD 14)

target_link_libraries(tests gtest displaylib)

add_test(
	NAME google_tests
	COMMAND tests
)