add_library(displaylib
	window.cc window.h
	functions.cc functions.h
	sdlobject.cc sdlobject.h
	surface.cc surface.h
	surface3D.cc surface3D.h
	objects.cc objects.h
	vector.h
	matrix.cc matrix.h
)
set_property(TARGET displaylib PROPERTY CXX_STANDARD 14)
target_link_libraries(displaylib SDL2)
target_include_directories(displaylib INTERFACE ..)
