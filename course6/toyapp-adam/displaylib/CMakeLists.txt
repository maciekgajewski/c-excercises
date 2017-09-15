add_library(displaylib
	camera.cc camera.h
	color.h
	cube.cc cube.h
	sdlobject.cc sdlobject.h
	surface_2d.cc surface_2d.h
	surface_3d.cc surface_3d.h
	window.cc window.h)

target_link_libraries(displaylib SDL2)
