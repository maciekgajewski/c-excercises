add_library(displaylib
	camera.cc
	cube.cc
	scene.cc
	sdlobject.cc
	surface.cc
	window.cc)

set_property(TARGET displaylib PROPERTY CXX_STANDARD 14)
target_link_libraries(displaylib SDL2)
