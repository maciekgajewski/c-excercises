add_library(displaylib
	camera.cc camera.h
	color.h
	cube.cc cube.h
	scene.cc scene.h
	sdlobject.cc sdlobject.h
	surface.cc surface.h
	window.cc window.h)

target_link_libraries(displaylib SDL2)
