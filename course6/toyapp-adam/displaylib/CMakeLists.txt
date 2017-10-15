add_library(displaylib
	camera.cc camera.h
	color.h
	mesh.cc mesh.h
	mesh_util.cc mesh_util.h
	sdlobject.cc sdlobject.h
	surface_2d.cc surface_2d.h
	surface_3d.cc surface_3d.h
	window.cc window.h)

target_link_libraries(displaylib SDL2)
