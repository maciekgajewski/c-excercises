file(GLOB DISPLAYLIB_SRCS *.cc *.h)

add_library(displaylib
	${DISPLAYLIB_SRCS}
)

set_property(TARGET displaylib PROPERTY CXX_STANDARD 14)
target_link_libraries(displaylib SDL2)
target_include_directories(displaylib INTERFACE ..)
