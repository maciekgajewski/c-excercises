add_library(util
	clock.h clock.cc
	)

set_property(TARGET util PROPERTY CXX_STANDARD 14)

target_link_libraries(util SDL2)