add_library(drawlib
	primitives.cc primitives.h
	index.h
)

set_property(TARGET drawlib PROPERTY CXX_STANDARD 14)
target_link_libraries(drawlib displaylib)

target_include_directories(drawlib INTERFACE ..)
