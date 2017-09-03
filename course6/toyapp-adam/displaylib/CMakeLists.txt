add_library(displaylib
	clock.cc
	cube.cc
	keyboard.cc
	matrix.cc
	scene.cc
	sdlobject.cc
	surface.cc
	transform.cc
	vector.cc
	window.cc)

set_property(TARGET displaylib PROPERTY CXX_STANDARD 14)
target_link_libraries(displaylib SDL2)
target_include_directories(displaylib INTERFACE ..)
