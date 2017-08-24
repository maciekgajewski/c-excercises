add_library(displaylib
	cube.cc
	functions.cc
	sdlobject.cc
	surface.cc
	vector.cc
	window.cc
)
set_property(TARGET displaylib PROPERTY CXX_STANDARD 14)
target_link_libraries(displaylib SDL2)
target_include_directories(displaylib INTERFACE ..)
target_include_directories(displaylib PUBLIC C:/lib/SDL2/include)
