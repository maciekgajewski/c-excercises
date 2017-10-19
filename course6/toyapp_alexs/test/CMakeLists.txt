file(GLOB unittests_SRCS *.cc)

add_executable(unittests ${unittests_SRCS})

set_property(TARGET unittests PROPERTY CXX_STANDARD 14)

target_link_libraries(unittests gtest displaylib)

add_test(
	NAME unittests
	COMMAND unittests
)
